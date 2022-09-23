#include "minishell.h"

int	count_process(t_node *node)
{
	int	cnt;

	cnt = 1;
	while (node->right)
	{
		++cnt;
		node = node->right;
	}
	return (cnt);
}

void	format_specifier(void (*f[])(char **))
{
	f[0] = builtin_echo;
	f[1] = builtin_cd;
	f[2] = builtin_pwd;
	f[3] = builtin_export;
	f[4] = builtin_unset;
	f[5] = builtin_env;
	f[6] = builtin_exit;
}

int	is_builtin_func(t_node *cmd)
{
	int	func;

	func = -1;
	if (cmd && cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->content, "echo", 5))
			func = 0;
		else if (!ft_strncmp(cmd->content, "cd", 3))
			func = 1;
		else if (!ft_strncmp(cmd->content, "pwd", 4))
			func = 2;
		else if (!ft_strncmp(cmd->content, "export", 7))
			func = 3;
		else if (!ft_strncmp(cmd->content, "unset", 6))
			func = 4;
		else if (!ft_strncmp(cmd->content, "env", 4))
			func = 5;
		else if (!ft_strncmp(cmd->content, "exit", 5))
			func = 6;
	}
	return (func);
}

char	**lst_to_2d_array(t_node *arg)
{
	char	**ptr;
	int		size;
	int		i;

	size = ft_lstsize(arg);
	i = -1;
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	while (++i < size)
	{
		ptr[i] = ft_strdup(arg->content);
		arg = arg->right;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	dup_frame(int fd, int std)
{
	if (dup2(fd, std) == -1)
		system_call_error(errno);
	close(fd);
}

void	open_redir_file(char *file, int mode)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			system_call_error(errno);
		dup_frame(fd, STDIN_FILENO);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			system_call_error(errno);
		dup_frame(fd, STDOUT_FILENO);
	}
	else if (mode == APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			system_call_error(errno);
		dup_frame(fd, STDOUT_FILENO);
	}
}

void	redir_action(t_node *cur_redir)
{
	char	*file_name;

	if (!cur_redir)
		return ;
	if (cur_redir->type == N_REDIR)
	{
		file_name = cur_redir->right->right->content;
		if (!ft_strncmp(cur_redir->right->content, "<", 2))
			open_redir_file(file_name, READ);
		else if (!ft_strncmp(cur_redir->right->content, ">", 2))
			open_redir_file(file_name, WRITE);
		else if (!ft_strncmp(cur_redir->right->content, ">>", 3))
			open_redir_file(file_name, APPEND);
	}
	redir_action(cur_redir->left);
}

char	*search_path(char *cmd, char **env_arr)
{
	char	**other_paths;
	char	*path;
	char	*cmd_path;
	int		i;
	struct stat statbuf;

	i = -1;
	path = ft_strjoin_no_free("/", cmd);
	other_paths = NULL;
	while (env_arr[++i])
	{
		if (!ft_strncmp(env_arr[i], "PATH=", 5))
		{
			other_paths = ft_split(&env_arr[i][5], ':');
			break ;
		}
	}
	i = -1;
	while (other_paths[++i])
	{
		cmd_path = ft_strjoin_no_free(other_paths[i], path);
		if (!stat(cmd_path, &statbuf))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_2d(other_paths);
	free(path);
	return (cmd_path);
}

int	is_absolute_path(char *path)
{
	return (path[0] == '/');
}

int	is_relative_path(char *path)
{
	return (((path[0] == '.') && (path[1] == '/')) ||
			((path[0] == '.') && (path[1] == '.') && (path[2] == '/')));
}

char	*no_search_path(t_node *cur_cmd, char **args, char *cmd)
{
	char		cwd_buff[PATH_MAX];
	char		*path;
	struct stat statbuf;
	size_t		len;

	if (getcwd(cwd_buff, PATH_MAX) == 0)
	{
		free_2d(args);
		system_call_error(errno);
	}
	len = ft_strlen(cwd_buff);
	cwd_buff[len] = '/';
	cwd_buff[len + 1] = 0;
	path = ft_strjoin_no_free(cwd_buff, cmd);
	if (!path)
	{
		free_2d(args);
		exit(set_or_get_status(-1));
	}
	if (stat(path, &statbuf) == -1)
		cmd_not_found_error(cur_cmd);
	return (path);
}

void	cmd_action(t_node *cur_cmd, char **env_arr, FUNC_TYPE builtin[])
{
	char	*path;
	char	**args;
	int		func_idx;
	struct stat statbuf;

	args = lst_to_2d_array(cur_cmd);
	func_idx = is_builtin_func(cur_cmd);
	if (func_idx > -1)
		run_builtin(cur_cmd, builtin, func_idx, 0);
	else if (is_absolute_path(cur_cmd->content) || is_relative_path(cur_cmd->content))
	{
		(void)env_arr;
		if (stat(cur_cmd->content, &statbuf) == -1)
			cmd_not_found_error(cur_cmd);
		execve_frame(cur_cmd->content, args, env_arr);
	}
	else
	{
		path = search_path(cur_cmd->content, env_arr);
		if (!path)
			path = no_search_path(cur_cmd, args, cur_cmd->content);
		execve_frame(path, args, env_arr);
	}
}

void	execve_frame(char *path, char **args, char **env_arr)
{
	if (execve(path, args, env_arr) == -1)
		system_call_error(errno);
}

void	child_process(t_node *cur_phrase, char **env_arr, FUNC_TYPE builtin[])
{
	if (cur_phrase->left)
		redir_action(cur_phrase->left);
	if (cur_phrase->right)
		cmd_action(cur_phrase->right, env_arr, builtin);
	exit(0);
}

int get_child_exit_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	fork_frame(t_node *cur_process, FUNC_TYPE builtin[])
{
	int 	fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup_frame(fd[1], STDOUT_FILENO);
		child_process(cur_process->left, env_array, builtin);
	}
	else
	{
		close(fd[1]);
		dup_frame(fd[0], STDIN_FILENO);
	}
	cur_process = cur_process->right;
}

void	fork_process(t_struct *ds, int cnt, FUNC_TYPE builtin[])
{
	int		backup_fd;
	int		status;
	int 	loop;
	pid_t	pid;

	backup_fd = dup(STDIN_FILENO);
	loop = 0;
	while (cnt > ++loop)
		fork_frame(ds->root_node, builtin);
	pid = fork();
	if (pid == 0)
		child_process(ds->root_node->left, env_array, builtin);
	else
	{
		status = set_or_get_status(-1);
		waitpid(pid, &status, 0); // 마지막 프로세스
		set_or_get_status(get_child_exit_value(status));
		while (cnt-- > loop)
			wait(NULL);
		dup2(backup_fd, STDIN_FILENO);
	}
}

void	run_builtin(t_node *cur_phrase, FUNC_TYPE builtin[], int func, int ps_type)
{
	char	*cmd;
	char	**args;
	int		old_fd;

	if (ps_type)
	{
		if (cur_phrase->left)
		{
			old_fd = dup(STDOUT_FILENO);
			redir_action(cur_phrase->left);
		}
	}
	args = lst_to_2d_array(cur_phrase->right);
	cmd = ft_strdup(cur_phrase->right->content);
	builtin[func](args);
	free(cmd);
	free_2d(args);
	if (!ps_type)
		exit(0);
	else if (cur_phrase->left)
		dup_frame(old_fd, STDOUT_FILENO);
}

void	execute(t_struct *ds)
{
	int			process_cnt;
	int			func_idx;
	FUNC_TYPE	builtin[7];

	format_specifier(builtin);
	func_idx = is_builtin_func(ds->root_node->left->right);
	process_cnt = count_process(ds->root_node);
	if (process_cnt == 1 && func_idx > -1)
		run_builtin(ds->root_node->left, builtin, func_idx, 1);
	else
		fork_process(ds, process_cnt, builtin);
}
