#include "minishell.h"

void	builtin_exit(char **args)
{
	(void)args;
	exit(0);
}