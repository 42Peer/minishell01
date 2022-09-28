#include "../minishell.h"

int	builtin_arg_count(char **args)
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
	if (arg_cnt != 2)
	{
		printf("ERROR: syntax error!\n");
		set_or_get_status(1);
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

static int	env_reassignment(char *args, char *tmp, char **env_array, char **split)
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

int replace_value(char **args)
{
    char    **split;
	char	*tmp;
	int     i;
    int     replace_flag;

    split = ft_split(args[1], '=');
	tmp = if_value(split);
    i = -1;
    replace_flag = 0;
    while (env_array[++i] && !replace_flag)
        if ((!ft_strncmp(split[0], env_array[i], ft_strlen(split[0])))
		|| (tmp && !ft_strncmp(tmp, env_array[i], ft_strlen(tmp))))
			replace_flag = env_reassignment(args[1], tmp, &env_array[i], split);
    free_2d(split);
    free(tmp);
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
