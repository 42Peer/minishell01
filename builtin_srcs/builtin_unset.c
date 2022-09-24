#include "../minishell.h"

int	is_exist(char **args)
{
	int		i;

	i = -1;
	while (env_array[++i])
	{
		if (ft_strncmp(args[1], env_array[i], ft_strlen(args[1])) == 0)
			return (i);
	}
	i = -1;
	return (-1);
}

int	unset_work_condition(char **args)
{
	int	unset_i;

	if (!builtin_arg_count(args))
		return (-1);
	unset_i = is_exist(args);
	return (unset_i);
}

void	builtin_unset(char **args)
{
	char	**new;
	int		unset_i;
	int		i;

	unset_i = unset_work_condition(args);
	if (unset_i == -1)
		return ;
	i = 0;
	while (env_array[i])
		++i;
	new = ft_calloc(i, sizeof(char *));
	if (!new)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (env_array[++i])
	{
		if (i != unset_i)
			new[i] = ft_strdup(env_array[i]);
	}
	i = -1;
	while (env_array[++i])
		free(env_array[i]);
	free(env_array);
	env_array = new;
}
