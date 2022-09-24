#include "../minishell.h"

int	builtin_arg_count(char **args)
{
	int	arg_cnt;

	arg_cnt = 0;
	while (args[arg_cnt])
		++arg_cnt;
	if (arg_cnt != 2)
	{
		printf("ERROR: syntax error!\n");
		return (0);
	}
	return (1);
}

int	replace_value(char **args)
{
	char	**split;
	int		i;
	int		replace_flag;

	split = ft_split(args[1], '=');
	i = -1;
	replace_flag = 0;
	while (env_array[++i])
	{
		if (ft_strncmp(split[0], env_array[i], ft_strlen(split[0])) == 0)
		{
			free(env_array[i]);
			env_array[i] = ft_strdup(args[1]);
			replace_flag = 1;
			break ;
		}
	}
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (replace_flag);
}

void	builtin_export(char **args)
{
	char	**new;
	int		i;

	if (!builtin_arg_count(args))
		return ;
	if (replace_value(args))
		return ;
	i = 0;
	while (env_array[i])
		++i;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (env_array[++i])
		new[i] = ft_strdup(env_array[i]);
	new[i++] = ft_strdup(args[1]);
	i = -1;
	while (env_array[++i])
		free(env_array[i]);
	free(env_array);
	env_array = new;
}
