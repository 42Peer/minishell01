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

int	is_builtin_func(t_node *node)
{
	node = node->left;	// phrase
	node = node->right;	// cmd
	if (node->type == T_WORD)
	{
		if (ft_strncmp(node->content, "cd", 3) == 0
			|| ft_strncmp(node->content, "pwd", 4) == 0
			|| ft_strncmp(node->content, "export", 7) == 0
			|| ft_strncmp(node->content, "env", 4) == 0
			|| ft_strncmp(node->content, "exit", 5) == 0)
			return (1);
		return (0);
	}
	else
		return (0);
}

void	multi_process(t_struct *ds, int cnt)
{
	int		backup_fd;
	pid_t	pid;
	t_node	*cur_process;
	int		status;

	backup_fd = dup(STDIN_FILENO);
	cur_process = ds->root_node;
	while (--cnt >= 1)
	{
		int fd[2];
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			printf("!ALERT! %d 자식 프로세스 명령어 실행\n", cnt);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			exit(0);
			// 자식프로세스 명령어 실행(cur_process, evnp);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		cur_process = cur_process->right;
	}
	pid = fork();
	if (pid == 0)
	{
		printf("!ALERT! %d 자식 프로세스 명령어 실행\n", cnt);
		exit(0);
		// 자식프로세스 명령어 실행(cur_process, evnp);
	}
	else
	{
		dup2(0, backup_fd);
		status = status_error(0);
		waitpid(pid, &status, 0); // 마지막 프로세스
		status_error(status);
		while (cnt - 1)
			wait(NULL);
		dup2(backup_fd, STDIN_FILENO);
	}
}

void	execute(t_struct *ds)
{
	t_node	*root;
	int		process_cnt;

	root = ds->root_node;
	process_cnt = count_process(root);
	printf("!ALERT! process는 %d개입니다.\n", process_cnt);
	if (process_cnt == 1 && is_builtin_func(root))
		printf("!ALERT! main에서 실행하기.\n");
		// main에서 실행함수(ds);
	else
		// printf("fork 후 실행하기.\n");
		multi_process(ds, process_cnt);
		// fork 후 실행함수();
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

void	fork_frame(t_node *cur_root, char **envp)
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
		close(fd[0]);
		dup_frame(fd[1], STDOUT_FILENO);
		ps_action(cur_root->left, envp);
//		execvision(ps_root->left, envp);
	}
	else
	{
		close(fd[1]);
		dup_frame(fd[0], STDIN_FILENO);
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
		fork_frame(root_node, envp);
		root_node = root_node->right;
	}
	while (--count >= 0)
		waitpid(-1, 0, 0);
    // 저장했던 입력방향 다시 재지정.
}
*/