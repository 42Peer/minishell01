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

void builtin_echo(char **args)
{
	(void)args;
	printf("echo\n");
}
void builtin_cd(char **args)
{
	(void)args;
	printf("cd\n");
}
void builtin_export(char **args)
{
	(void)args;
	printf("export\n");
}
void builtin_unset(char **args)
{
	(void)args;
	printf("unset\n");
}
void builtin_env(char **args)
{
	(void)args;
	printf("env\n");
}

void builtin_exit(char **args)
{
	(void)args;
	printf("exit\n");
	exit(0);
}

void	builtin_pwd(char **cmd)
{
	(void)cmd;
	printf("pwd\n");
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
	if (cmd->type == T_WORD)
	{
		if (ft_strncmp(cmd->content, "echo", 5) == 0)
			func = 0;
		else if (ft_strncmp(cmd->content, "cd", 4) == 0)
			func = 1;
		else if (ft_strncmp(cmd->content, "pwd", 7) == 0)
			func = 2;
		else if (ft_strncmp(cmd->content, "export", 4) == 0)
			func = 3;
		else if (ft_strncmp(cmd->content, "unset", 5) == 0)
			func = 4;
		else if (ft_strncmp(cmd->content, "env", 5) == 0)
			func = 5;
		else if (ft_strncmp(cmd->content, "exit", 5) == 0)
			func = 6;
	}
	return (func);
}

// void	execvision(t_node *ps_cmd, char **envp)
// {
// 	char	**cmd;
// 	char	*program_path;

// 	cmd = ;
// 	program_path = search_path(ps_cmd, envp);
// 	if (execve(program_path, cmd, envp) == -1)
// 		system_call_error();
// }

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
	write(2, "test\n", 5);        // for test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (cur_redir->type == N_REDIR)//
	{
		file_name = cur_redir->right->right->content;
		// printf("%s %s\n", cur_redir->right->content, file_name);
		if (!ft_strncmp(cur_redir->right->content, "<", 2))
			open_redir_file(file_name, READ);
		else if (!ft_strncmp(cur_redir->right->content, ">", 2))
			open_redir_file(file_name, WRITE);
		else if (!ft_strncmp(cur_redir->right->content, ">>", 3))
			open_redir_file(file_name, APPEND);
	}
	redir_action(cur_redir->left);
}

char	*search_path(char *cmd, t_env *env_lst)
{
	char	**other_paths;
	char	*path;
	char	*cmd_path;
	int		i;
	struct stat statbuf;

	i = -1;
	path = ft_strjoin_no_free("/", cmd);
	other_paths = NULL;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->key, "PATH", 5))
		{
			other_paths = ft_split(env_lst->value, ':');
			break ;
		}
		env_lst = env_lst->next;
	}
	i = -1;
	while (other_paths[++i])
	{
		cmd_path = ft_strjoin_no_free(other_paths[i], path);
		if (stat(cmd_path, &statbuf) == 0)
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

void	cmd_action(t_node *cur_cmd, t_env *env_lst, char **env_arr)
{
	char	*path;
	char	*cmd;
	char	**args;
	char	cwd_buff[256];
	size_t	len;
	// FUNC_TYPE	builtin[7];
	int		func_idx;
	struct stat statbuf;

	args = lst_to_2d_array(cur_cmd);
	func_idx = is_builtin_func(cur_cmd);
	if (func_idx > -1)
	{
		// run_builtin(cur_cmd, builtin, func_idx);
		exit(0);
	}
	else if (is_absolute_path(cur_cmd->content) || is_relative_path(cur_cmd->content))
	{
		(void)env_arr;
		if (execve(cur_cmd->content, args, check) == -1)
			system_call_error(CMD_NOT_FOUND);
	}
	else
	{
		cmd = cur_cmd->content;
		path = search_path(cmd, env_lst);
		if (!path)
		{
			if (getcwd(cwd_buff, 256) == 0)
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
				exit(set_or_get_status(0));
				// printf("cmd or cwd_buff is null\n");
			}
			if (stat(path, &statbuf) == 0)
				system_call_error(CMD_NOT_FOUND);
		}
		// printf("cmd, path = %s\n", path);
		if (execve(path, args, check) == -1)
		{
			system_call_error(errno);
		}
	}
}

void	child_process(t_node *cur_phrase, char **env_arr, t_env *env_lst)
{
	// char	*redir;
	// char	*filename;
	// char	**args;

	// printf("child_process->right->content > %s\n", cur_phrase->right->content);
	// if (cur_phrase->left && cur_phrase->left->type == N_REDIR) <-- 필요없는것같음.
	if (cur_phrase->left)
	{
		write(2, "redir\n", 5);
		// printf("REDIR 처리 \n");
		redir_action(cur_phrase->left);
	}
	// if (cur_phrase->right && cur_phrase->right->type == T_WORD)
	if (cur_phrase->right)
	{
		// printf("커맨드처리 \n");
		cmd_action(cur_phrase->right, env_lst, env_arr);
	}
	// printf("child process end \n");
	exit(0);
}

void	fork_process(t_struct *ds, int cnt)
{
	int		backup_fd;
	pid_t	pid;
	t_node	*cur_process;
	int		status;
	int 	loop;

	backup_fd = dup(STDIN_FILENO);
	cur_process = ds->root_node;
	loop = 0;
	while (cnt > ++loop)
	{
		int fd[2];
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			// if (cmd 마지막일때)
				// 자식프로세스명령실행
			// else
			// {
				// printf("!ALERT! %d 자식 프로세스 명령어 실행\n", loop);
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				// printf("child\n");
				child_process(cur_process->left, ds->env_array, ds->head_env);
			// }
		}
		else
		{
			// if (last cmd)
				// status 함수 실행
//			else
//			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
//			}
		}
		cur_process = cur_process->right;
	}
	pid = fork();
	// printf("pid = %d\n", pid);
	if (pid == 0)
	{
		// printf("!ALERT! %d 마지막 자식 프로세스 명령어 실행\n", cnt);
		child_process(cur_process->left, ds->env_array, ds->head_env);
	}
	else
	{
		status = set_or_get_status(0); // <- 필요없는거같아.
		waitpid(pid, &status, 0); // 마지막 프로세스
		set_or_get_status(status);
		while (cnt-- > 1)
			wait(NULL);
		dup2(backup_fd, STDIN_FILENO);
	}
}

void	run_builtin(t_node *cur_phrase, FUNC_TYPE builtin[], int func)
{
	char	*cmd;
	char	**args;

	if (cur_phrase->left)
	{
		// printf("REDIR 처리 \n");
		redir_action(cur_phrase->left);
	}
	cmd = ft_strdup(cur_phrase->right->content);
	args = lst_to_2d_array(cur_phrase->right->right);
	builtin[func](args);
	free(cmd);
	free(args);
}

void	execute(t_struct *ds)
{
	t_node	*root;
	int		process_cnt;
	FUNC_TYPE	builtin[7];
	int	func_idx;

	format_specifier(builtin);
	root = ds->root_node;
	// if (root->left->right == NULL )
	// 	return ;
	func_idx = is_builtin_func(root->left->right);
	process_cnt = count_process(root);
	// printf("!ALERT! process는 %d개입니다.\n", process_cnt);
	if (process_cnt == 1 && func_idx > -1)
	{
		// printf("!ALERT! main에서 실행하기.\n");
		run_builtin(ds->root_node->left, builtin, func_idx);
	}
	else
		fork_process(ds, process_cnt);
		// printf("fork 후 실행하기.\n");
}




/*
void	dup_frame(int fd, int std)
{
	if (dup2(fd, std) == -1)
		system_call_error();
	close(fd);
}

void	redir_file(char *file, int mode)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			system_call_error();
		dup_frame(fd, STDIN_FILENO);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			system_call_error();
		dup_frame(fd, STDOUT_FILENO);
	}
	else if (mode == APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			system_call_error();
		dup_frame(fd, STDIN_FILENO);
	}
}

void	fork_frame(t_node *cur_root, char **envp, int type)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		system_call_error();
	pid = fork();
	if (pid == -1)
		system_call_error();
	else if (pid == 0)
	{
		if (type == END)
			execvision();
		else
		{
			close(fd[0]);
			dup_frame(fd[1], STDOUT_FILENO);
			ps_action(cur_root->left, envp);
		}
	}
	else
	{
		if (type == END)
			get_status();
		else
		{	
			close(fd[1]);
			dup_frame(fd[0], STDIN_FILENO);
		}
	}
}

void	redir_action(t_node *cur_redir)
{
	if (!cur_redir)
		return ;
	if (cur_redir->type == N_REDIR)
	{
		filename = cur_redir->right->right->content;
		if (ft_strncmp(cur_redir->right->content, "<", 2))
			redir_file(filename, READ);
		else if (ft_strncmp(cur_redir->right->content, ">", 2))
			redir_file(filename, WRITE);
		else
			redir_file(filename, APPEND);
	}
	redir_action(cur_redir->left);



	if (cur_redir->type == T_REDIR)
		redir_action(cur_redir->right);
	if (cur_redir->type == T_WORD)
	{
		if (ft_strncmp(cur_redir->content, "<", 2))
			redir_file(cur_redir->content, READ);
		else if (ft_strncmp(cur_redir->content, ">", 2))
			redir_file(cur_redir->content, WRITE);
		else
			redir_file(cur_redir->content, APPEND);
	}
}

void	cmd_action(t_node *cur_cmd)
{
	
}

void	ps_action(t_node *cur_phrase, char **envp)
{
	if (!cur_phrase)
		return ;
	if (cur_phrase->left->type == N_REDIR)
		redir_action(cur_phrase->right);
	else if (cur_phrase->right->type == T_WORD)
		cmd_action(cur_phrase->right);
}

void	execvision(t_node *ps_cmd, char **envp)
{
	char	**cmd;
	char	*program_path;

	cmd = ;
	program_path = search_path(ps_cmd, envp);
	if (execve(program_path, cmd, envp) == -1)
		system_call_error();
}

void	get_ps(t_node *root_node, char **envp)
{
    int     size;
    int     count;

    count = 0;
    size = ft_lstsize(root_node);
    while (count++ < size)
	{
		if (count + 1 == size)
			fork_frame(root_node, envp, END);
		else
			fork_frame(root_node, envp, CONTINUE);
		root_node = root_node->right;
	}
	while (--count >= 0)
		waitpid(-1, 0, 0);
    // 저장했던 입력방향 다시 재지정.
}
*/