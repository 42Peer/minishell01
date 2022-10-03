#include "../../minishell.h"

void	make_g_env_array(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		++i;
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		system_call_error(ALLOC_FAIL);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	g_env_array = env;
}
