#include "../../minishell.h"

void	put_paths(int *p_i, char ***p_other_paths)
{
	while (g_env_array[++(*p_i)])
	{
		if (!ft_strncmp(g_env_array[*p_i], "PATH=", 5))
		{
			*p_other_paths = ft_split(&g_env_array[*p_i][5], ':');
			break ;
		}
	}
}

char	*search_path(char *cmd)
{
	char		**other_paths;
	char		*path;
	char		*cmd_path;
	int			i;
	struct stat	statbuf;

	if (cmd[0] == '\0')
		return (NULL);
	i = -1;
	path = ft_strjoin_no_free("/", cmd);
	other_paths = NULL;
	put_paths(&i, &other_paths);
	i = -1;
	while (other_paths[++i])
	{
		cmd_path = ft_strjoin_no_free(other_paths[i], path);
		if (!stat(cmd_path, &statbuf))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_2d(other_paths);
	free(path);
	return (cmd_path);
}

int	is_absolute_path(char *path)
{
	return (path[0] == '/');
}

int	is_relative_path(char *path)
{
	return (((path[0] == '.') && (path[1] == '/'))
		|| ((path[0] == '.') && (path[1] == '.') && (path[2] == '/')));
}

char	*no_search_path(t_node *cur_cmd, char **args, char *cmd)
{
	char		cwd_buff[PATH_MAX];
	char		*path;
	struct stat	statbuf;
	size_t		len;

	if (cmd[0] == '\0')
		return (NULL);
	if (getcwd(cwd_buff, PATH_MAX) == 0)
	{
		free_2d(args);
		system_call_error(errno);
	}
	len = ft_strlen(cwd_buff);
	cwd_buff[len] = '/';
	cwd_buff[len + 1] = 0;
	path = ft_strjoin_no_free(cwd_buff, cmd);
	if (!path)
	{
		free_2d(args);
		exit(set_or_get_status(-1));
	}
	if (stat(path, &statbuf) == -1)
		cmd_not_found_error(cur_cmd);
	return (path);
}
