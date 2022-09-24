#include "minishell.h"

int	is_exist(char **args)
{
	int		i;

	i = -1;
	while (check[++i])
	{
		if (ft_strncmp(args[1], check[i], ft_strlen(args[1])) == 0)
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
	while (check[i])
		++i;
	new = ft_calloc(i, sizeof(char *));
	if (!new)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (check[++i])
	{
		if (i != unset_i)
			new[i] = ft_strdup(check[i]);
	}
	i = -1;
	while (check[++i])
		free(check[i]);
	free(check);
	check = new;
}
