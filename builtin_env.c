#include "minishell.h"

void	builtin_env(char **args)
{
	(void)args;
	int	i;

	i = -1;
	while (check[++i])
		printf("%s\n", check[i]);
}
