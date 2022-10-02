#include "../../minishell.h"

void	e_dup2(int fd, int std)
{
	if (dup2(fd, std) == -1)
		system_call_error(errno);
	close(fd);
}

void	redir_action(t_node *cur_redir, int b_child_process, int *predir_erred)
{
	char	*file_name;

	if (!cur_redir || *predir_erred)
		return ;
	if (cur_redir->type == N_REDIR)
	{
		file_name = cur_redir->right->right->content;
		if (!ft_strncmp(cur_redir->right->content, "<", 2))
			*predir_erred = open_redir_file(file_name, READ, b_child_process);
		else if (!ft_strncmp(cur_redir->right->content, ">", 2))
			*predir_erred = open_redir_file(file_name, WRITE, b_child_process);
		else if (!ft_strncmp(cur_redir->right->content, ">>", 3))
			*predir_erred = open_redir_file(file_name, APPEND, b_child_process);
		else
			printf("error!\n");
	}
	redir_action(cur_redir->left, b_child_process, predir_erred);
}

int	redir_error(int b_child_process)
{
	if (b_child_process)
	{
		system_call_error(errno);
		return (0);
	}
	builtin_error();
	return (1);
}

int	open_redir_file(char *file, int mode, int b_child_process)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			return (redir_error(b_child_process));
		e_dup2(fd, STDIN_FILENO);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			return (redir_error(b_child_process));
		e_dup2(fd, STDOUT_FILENO);
	}
	else if (mode == APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return (redir_error(b_child_process));
		e_dup2(fd, STDOUT_FILENO);
	}
	return (0);
}
