#include "minishell.h"

void	fork_frame(t_node *ps_root, char **envp, int outfile, int mode)
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
		if (mode == END)
			dup_frame(outfile, STDOUT_FILENO);
		else
			dup_frame(fd[1], STDOUT_FILENO);
		execvision(ps_root, envp);
	}
	else
	{
		close(fd[1]);
		dup_frame(fd[0], STDIN_FILENO);
	}
}

void	dup_frame(int fd, int std)
{
	if (dup2(fd, std) == -1)
		system_call_error();
	close(fd);
}

int	open_frame(char *file, int mode)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			system_call_error();
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			system_call_error();
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			system_call_error();
	}
	return (fd);
}

void	execvision(char *argv, char **envp)
{
	char	**cmd;
	char	*program_path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		system_call_error();
	program_path = search_path(cmd[0], envp);
	if (execve(program_path, cmd, envp) == -1)
		system_call_error();
}

void	str_isfree(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

char	*search_path(char *cmd, char **envp)
{
	char	**other_paths;
	char	*path;
	char	*cmd_path;
	int		i;

	i = -1;
	path = ft_strjoin("/", cmd);
	if (!path)
		system_call_error();
	while (!ft_strnstr(envp[++i], "PATH", 4))
		;
	other_paths = ft_split(envp[i] + 5, ':');
	if (!other_paths)
		system_call_error();
	i = -1;
	while (other_paths[++i])
	{
		cmd_path = ft_strjoin(other_paths[i], path);
		if (!access(cmd_path, X_OK))
			break ;
		free(cmd_path);
	}
	str_isfree(other_paths);
	free(path);
	return (cmd_path);
}

void	get_ps(t_struct *ds, char **envp)
{
    int     size;
    int     count;

    count = 0;
    size = ft_lstsize(ds->root_node->right) + 1;
    while (count++ <= size)
	{
		if (count == size)
			fork_frame(ds->root_node->right, envp, outfile, END);
		else
			fork_frame(ds->root_node->right, envp, outfile, CONTINUE);
	}
	while (--count >= 0)
		waitpid(-1, 0, 0);
}


