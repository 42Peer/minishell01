#include "../minishell.h"

int	unset_no_args(char **args)
{
	int	cnt;

	cnt = ft_arrlen(args);
	if (cnt == 1)
	{
		printf("unset: not enough arguments\n");
		set_or_get_status(1);
		return (1);
	}
	return (0);
}

int	is_valid_arg(char *arg)
{
	int	chr_idx;
	int	ch;

	chr_idx = 0;
	while (arg[chr_idx])
	{
		ch = arg[chr_idx];
		if ((chr_idx == 0) && (ch >= '0' && ch <= '9'))
			return (0);
		if (!ft_isalnum(ch) && (ch != '_'))
			return (0);
		++chr_idx;
	}
	return (1);
}

int	is_exist(char *arg)
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
		if (ft_strncmp(arg, split[0], ft_strlen(arg) + 1) == 0)
			exist_i = i;
		j = -1;
		while (split[++j])
			free(split[j]);
		free(split);
	}
	return (exist_i);
}

int	unset_work_condition(char *arg)
{
	int	exist_i;

	if (!is_valid_arg(arg))
	{
		printf("unset: `%s': not a valid identifier\n", arg);
		set_or_get_status(1);
		return (-1);
	}
	exist_i = is_exist(arg);
	return (exist_i);
}

void	builtin_unset(char **args)
{
	char	**new;
	int		exist_i;
	int		i;
	int		j;
	int		new_i;

	if (unset_no_args(args))
		return ;
	i = -1;
	while (args[++i])
	{
		exist_i = unset_work_condition(args[i]);
		if (exist_i == -1)
			continue ;
		j = ft_arrlen(env_array);
		new = ft_calloc(j, sizeof(char *));
		j = -1;
		new_i = 0;
		while (env_array[++j])
			if (j != exist_i)
				new[new_i++] = env_array[j];
		free(env_array[exist_i]);
		free(env_array);
		env_array = new;
	}
}
