#include "minishell.h"

int		export_arg_count(char **args)
{
	int 	arg_cnt;

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

void	builtin_export(char **args)
{
	char	**new;
	int 	i;

	if (!export_arg_count(args))
		return builtin_env(NULL);
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
