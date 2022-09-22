#include "minishell.h"

char	*search_from_envp(char *word)
{
	int	i;
	char	*path;
	char	**ret_split;

	i = 0;
	path = NULL;
	while (check[i])
	{
		if (ft_strncmp(check[i], word, ft_strlen(word)) == 0) // 찾으면 0
		{
			ret_split = ft_split(check[i], '=');
			path = ft_strdup(ret_split[1]);
			free_2d(ret_split);
			break ;
		}
		++i;
	}
	return (path);
}

void builtin_cd(char **args)
{
	int		ret;
	char	*path;

	path = args[1];
	if (!(args[1]))
		return ;
	else if (ft_strncmp(path, "~", 1) == 0)
	{
		path = search_from_envp("HOME");
		ret = chdir(path);
		free(path);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		path = search_from_envp("OLDPWD");
		ret = chdir(path);
		free(path);
	}
	else
		ret = chdir(path);
	if (!ret)
	{
		set_or_get_status(errno);
		return ;
	}
}
