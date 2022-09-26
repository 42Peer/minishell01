#include "../../minishell.h"

void	ft_exit(int error)
{
	set_or_get_status(error);
	exit(error);
}

int	set_or_get_status(int error)
{
	static int	status;

	if (error >= 0)
		status = error;
	return (status);
}

void	cmd_not_found_error(t_node *cmd)
{
	char	*err_str;

	err_str = "❀ ❂ smash 🍾 ";
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	err_str = cmd->content;
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	err_str = " 🍾 hey~ command not found\n";
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	ft_exit(CMD_NOT_FOUND);
}

void	system_call_error(int error)
{
	char	*err_str;

	err_str = strerror(error);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
	if (error == ALLOC_FAIL)
		ft_exit(ALLOC_FAIL);
	else if (error == EACCES || error == ENOEXEC)
		ft_exit(EXEC_FILE_FAIL);
	else
		ft_exit(GENERAL_ERROR);
}

void	builtin_error(void)
{
	char	*err_str;

	err_str = strerror(errno);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
	set_or_get_status(GENERAL_ERROR);
}
