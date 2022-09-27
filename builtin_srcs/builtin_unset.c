#include "../minishell.h"

int	is_valid_args(char **args)
{
	int	str_idx;
	int	chr_idx;
	int	ch;

	str_idx = 0;
	while (args[str_idx])
	{
		chr_idx = 0;
		while (args[str_idx][chr_idx])
		{
			ch = args[str_idx][chr_idx];
			if ((chr_idx == 0) && (ch >= '0' && ch <= '9'))
				return (0);
			if (!ft_isalnum(ch) && (ch != '_'))
				return (0);
			++chr_idx;
		}
		++str_idx;
	}
	return (1);
}


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

int	builtin_unset_arg_count(char **args)
{
	int	arg_cnt;

	arg_cnt = 0;
	while (args[arg_cnt])
		++arg_cnt;
	if (arg_cnt == 1)
		return (0);
	if (!is_valid_args(args))
	{
		printf("ERROR: syntax error!\n");
		set_or_get_status(1);
		return (0);
	}
	return (1);
}

int	unset_work_condition(char **args)
{
	int	exist_i;

	if (!builtin_unset_arg_count(args))
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
