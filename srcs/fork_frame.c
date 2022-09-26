#include "../minishell.h"

int	get_child_exit_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	child_process(t_node *cur_phrase, char **env_arr, FUNC_TYPE builtin[])
{
	if (cur_phrase->left)
		redir_action(cur_phrase->left);
	if (cur_phrase->right)
		cmd_action(cur_phrase->right, env_arr, builtin);
	exit(0);
}

void	fork_frame(t_node **cur_process, FUNC_TYPE builtin[])
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup_frame(fd[1], STDOUT_FILENO);
		child_process((*cur_process)->left, env_array, builtin);
	}
	else
	{
		close(fd[1]);
		dup_frame(fd[0], STDIN_FILENO);
	}
	*cur_process = (*cur_process)->right;
}

void	fork_process(t_struct *ds, int cnt, FUNC_TYPE builtin[])
{
	int		backup_fd;
	int		status;
	int		loop;
	pid_t	pid;

	backup_fd = dup(STDIN_FILENO);
	loop = 0;
	while (cnt > ++loop)
		fork_frame(&ds->root_node, builtin);
	pid = fork();
	if (pid == 0)
		child_process(ds->root_node->left, env_array, builtin);
	else
	{
		status = set_or_get_status(-1);
		waitpid(pid, &status, 0);
		set_or_get_status(get_child_exit_value(status));
		while (cnt-- > loop)
			wait(NULL);
		dup2(backup_fd, STDIN_FILENO);
	}
}
