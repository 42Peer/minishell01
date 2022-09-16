#include "minishell.h"

void	dup_frame(int fd, int std)
{
	if (dup2(fd, std) == -1)
		get_error();
	close(fd);
}

int	open_frame(char *file, int mode)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			get_error();
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			get_error();
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			get_error();
	}
	return (fd);
}


void	fork_frame(t_node *ps_root, char **envp, int outfile, int mode)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		get_error();
	pid = fork();
	if (pid == -1)
		get_error();
	else if (pid == 0)
	{
		close(fd[0]);
		dup_frame(fd[1], STDOUT_FILENO);
		execvision(ps_root, envp);
	}
	else
	{
		close(fd[1]);
		dup_frame(fd[0], STDIN_FILENO);
	}
}

void	get_ps(t_struct *ds, char **envp)
{
    int     size;
    int     count;

    count = 0;
    size = ft_lstsize(ds->root_node->right) + 1;
    while (count++ <= size)
	{
		fork_frame(ds->root_node->right, envp, , CONTINUE);
	}
    waitpid(pid, status, 0);
	while (--count >= 0)
		waitpid(-1, 0, 0);
    // 저장했던 입력방향 다시 재지정.
}
