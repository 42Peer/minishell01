#include "../minishell.h"

int	is_exist(char **args)
{
	int		i;
	int		j;
	char	**split;
	int		exist_i;

	exist_i = -1;
	i = -1;
	while (exist_i == -1 && env_array[++i])
	{
		split = ft_split(env_array[i], '=');
		if (ft_strncmp(args[1], split[0], ft_strlen(args[1]) + 1) == 0)
			exist_i = i;
		j = -1;
		while (split[++j])
			free(split[j]);
		free(split);
	}
	return (exist_i);
}

int	unset_work_condition(char **args)
{
	int	exist_i;

	if (!builtin_arg_count(args))
		return (-1);
	exist_i = is_exist(args);
	return (exist_i);
}

void	builtin_unset(char **args)
{
	char	**new;
	int		exist_i;
	int		i;
	int		j;

	exist_i = unset_work_condition(args);
	if (exist_i == -1)
		return ;
	i = 0;
	while (env_array[i])
		++i;
	new = ft_calloc(i, sizeof(char *));
	i = -1;
	j = 0;
	while (env_array[++i])
		if (i != exist_i)
			new[j++] = ft_strdup(env_array[i]);
	i = -1;
	while (env_array[++i])
		free(env_array[i]);
	free(env_array);
	env_array = new;
}
