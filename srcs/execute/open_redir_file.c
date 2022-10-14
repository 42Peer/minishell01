#include "../../minishell.h"

void	e_dup2(int fd, int std)
{
	if (dup2(fd, std) == -1)
		system_call_error(errno);
	close(fd);
}

int	redir_action(t_node *cur_redir, int is_child)
{
	char	*file_name;
	int		error;

	error = 0;
	if (!cur_redir)
		return (error);
	if (cur_redir->type == N_REDIR)
	{
		file_name = cur_redir->right->right->content;
		if (!ft_strncmp(cur_redir->right->content, "<", 2))
			error = open_redir_file(file_name, READ, is_child);
		else if (!ft_strncmp(cur_redir->right->content, ">", 2))
			error = open_redir_file(file_name, WRITE, is_child);
		else if (!ft_strncmp(cur_redir->right->content, ">>", 3))
			error = open_redir_file(file_name, APPEND, is_child);
	}
	if (!error)
		redir_action(cur_redir->left, is_child);
	return (error);
}

int	redir_error(int error, int is_child)
{
	if (is_child)
	{
		system_call_error(error);
		return (0);
	}
	builtin_error();
	return (1);
}

int	open_redir_file(char *file, int mode, int is_child)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			return (redir_error(errno, is_child));
		e_dup2(fd, STDIN_FILENO);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			return (redir_error(errno, is_child));
		e_dup2(fd, STDOUT_FILENO);
	}
	else if (mode == APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return (redir_error(errno, is_child));
		e_dup2(fd, STDOUT_FILENO);
	}
	return (0);
}
