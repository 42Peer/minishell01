#include "../minishell.h"

int	print_or_export(char **args)
{
	int	arg_cnt;
	int	i;

	arg_cnt = 0;
	while (args[arg_cnt])
		++arg_cnt;
	if (arg_cnt == 1)
	{
		i = 0;
		while (env_array[++i])
			printf("%s\n", env_array[i]);
		set_or_get_status(0);
		return (0);
	}
	return (1);
}

static char	*if_value(char **split)
{
	char	*ptr;

	ptr = NULL;
	if (split[1])
	{
		ptr = ft_strdup(split[0]);
		ptr = save(ptr, '=', ft_strlen(ptr));
	}
	return (ptr);
}

static int	env_reassignment(char *args, char *tmp,
	char **env_array, char **split)
{
	int	flag;

	flag = 0;
	if (!tmp && (*env_array)[ft_strlen(split[0])] == '=')
		flag = 1;
	if (!flag && tmp)
	{
		free(*env_array);
		*env_array = ft_strdup(args);
		flag = 1;
	}
	return (flag);
}

int	replace_value(char *arg)
{
	char	**split;
	char	*tmp;
	int		i;
	int		replace_flag;

	split = ft_split(arg, '=');
	tmp = if_value(split);
	i = -1;
	replace_flag = 0;
	while (env_array[++i] && !replace_flag)
		if ((!ft_strncmp(split[0], env_array[i], ft_strlen(split[0])))
			|| (tmp && !ft_strncmp(tmp, env_array[i], ft_strlen(tmp))))
			replace_flag = env_reassignment(arg, tmp, &(env_array[i]), split);
	free_2d(split);
	free(tmp);
	return (replace_flag);
}

void	builtin_export(char **args)
{
	char	**new;
	int		i;
	int		j;

	if (!print_or_export(args))
		return ;
	i = 0;
	while (args[++i])
	{
		if (replace_value(args[i]))
			continue ;
		if (!is_valid_arg(args[i]))
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			continue ;
		}
		j = ft_arrlen(env_array);
		new = ft_calloc(j + 2, sizeof(char *));
		j = -1;
		while (env_array[++j])
			new[j] = env_array[j];
		new[j++] = ft_strdup(args[i]);
		free(env_array);
		env_array = new;
	}
}
