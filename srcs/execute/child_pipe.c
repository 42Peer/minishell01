#include "../../minishell.h"

int	get_child_exit_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	child_process(t_node *cur_phrase, FUNC_TYPE builtin[])
{
	int	old_stdin;

	old_stdin = dup(STDIN_FILENO);
	if (cur_phrase->left)
		redir_action(cur_phrase->left);
	if (cur_phrase->right)
		cmd_action(cur_phrase->right, builtin, old_stdin);
	exit(set_or_get_status(-1));
}

void	child_pipe(t_node **cur_process, FUNC_TYPE builtin[])
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		e_dup2(fd[1], STDOUT_FILENO);
		child_process((*cur_process)->left, builtin);
	}
	else
	{
		close(fd[1]);
		e_dup2(fd[0], STDIN_FILENO);
	}
	*cur_process = (*cur_process)->right;
}

void	fork_process(t_struct *ds, int cnt, FUNC_TYPE builtin[])
{
	int		backup_fd;
	int		status;
	int		loop;
	pid_t	pid;
	t_node	*cur_node;

	backup_fd = dup(STDIN_FILENO);
	cur_node = ds->root_node;
	loop = 0;
	while (cnt > ++loop)
		child_pipe(&cur_node, builtin);
	pid = fork();
	if (pid == 0)
		child_process(cur_node->left, builtin);
	else
	{
		status = 0;
		waitpid(pid, &status, 0);
		set_or_get_status(get_child_exit_value(status));
		while (cnt-- > loop)
			wait(NULL);
		e_dup2(backup_fd, STDIN_FILENO);
	}
}
