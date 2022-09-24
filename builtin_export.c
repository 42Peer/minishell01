#include "minishell.h"

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
	while (check[++i])
	{
		if (ft_strncmp(split[0], check[i], ft_strlen(split[0])) == 0)
		{
			free(check[i]);
			check[i] = ft_strdup(args[1]);
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
	while (check[i])
		++i;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (check[++i])
		new[i] = ft_strdup(check[i]);
	new[i++] = ft_strdup(args[1]);
	i = -1;
	while (check[++i])
		free(check[i]);
	free(check);
	check = new;
}
