#include "../../minishell.h"

int	get_child_exit_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	child_process(t_node *cur_phrase, t_func_type builtin[], int backup_fd)
{
	int	redir_errored;
	int	b_child_process;

	close(backup_fd);
	redir_errored = 0;
	b_child_process = 1;
	if (cur_phrase->left)
		redir_action(cur_phrase->left, b_child_process, &redir_errored);
	if (cur_phrase->right)
		cmd_action(cur_phrase->right, builtin);
	exit(set_or_get_status(-1));
}

void	child_pipe(t_node **cur_process, t_func_type builtin[],
				int backup_fd)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		e_dup2(fd[1], STDOUT_FILENO);
		child_process((*cur_process)->left, builtin, backup_fd);
	}
	else
	{
		close(fd[1]);
		e_dup2(fd[0], STDIN_FILENO);
	}
	*cur_process = (*cur_process)->right;
}

void	wait_for_remain_child_processes(void)
{
	int	status;

	while (1)
	{
		waitpid(-1, &status, 0);
		if (errno == ECHILD)
			break ;
	}
}

void	fork_process(t_head *p_head, int cnt, t_func_type builtin[])
{
	int		backup_fd;
	int		status;
	int		loop;
	pid_t	pid;
	t_node	*cur_node;

	backup_fd = dup(STDIN_FILENO);
	cur_node = p_head->node;
	loop = 0;
	while (cnt > ++loop)
		child_pipe(&cur_node, builtin, backup_fd);
	pid = fork();
	if (pid == 0)
		child_process(cur_node->left, builtin, backup_fd);
	else
	{
		e_dup2(backup_fd, STDIN_FILENO);
		status = 0;
		waitpid(pid, &status, 0);
		set_or_get_status(get_child_exit_value(status));
		wait_for_remain_child_processes();
	}
}
