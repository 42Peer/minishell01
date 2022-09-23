#include "minishell.h"

void	builtin_env(char **args)
{
	(void)args;
	int	i;

	i = -1;
	while (env_array[++i])
		printf("%s\n", env_array[i]);
	set_or_get_status(0);
}
