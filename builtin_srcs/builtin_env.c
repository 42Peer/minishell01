#include "../minishell.h"

int	ft_strchr(const char *str, int chr)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)chr)
			return (i);
		++i;
	}
	return (-1);
}

void	builtin_env(char **args)
{
	int	i;

	(void)args;
	if (ft_strncmp(args[1], "env", 4) != 0)
	{
		printf("env: %s: No such file or directory\n", args[1]);
		set_or_get_status(GENERAL_ERROR);
		return ;
	}
	i = -1;
	while (env_array[++i])
	{
		if (ft_strchr(env_array[i], '=') != -1)
			printf("%s\n", env_array[i]);
	}
	set_or_get_status(0);
}
