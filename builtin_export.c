#include "minishell.h"

void	builtin_export(char **args)
{
	char	**new;
	int 	arg_cnt;
	int 	i;

	arg_cnt = 0;
	while (args[arg_cnt])
		++arg_cnt;
	if (arg_cnt != 2) {
		printf("ERROR: syntax error!\n");
		return ;
	}
	i = 0;
	while (check[i])
		++i;
	new = (char **)malloc(sizeof(char *) * i + 2);
	if (!new)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (check[++i])
		new[i] = ft_strdup(check[i]);
	new[i++] = ft_strdup(args[1]);
	new[i] = NULL;
	while (check[++i])
		free(check[i]);
	free(check);
	check = new;
}