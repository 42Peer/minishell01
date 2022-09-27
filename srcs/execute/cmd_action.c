#include "../../minishell.h"

void	execve_frame(char *path, char **args, char **env_arr)
{
	if (opendir(path))
	{
		printf("-minishell: %s: Is a directory\n", path);
		return ;
	}
	if (execve(path, args, env_arr) == -1)
		system_call_error(errno);
}

char	**lst_to_2d_array(t_node *arg)
{
	char	**ptr;
	int		size;
	int		i;

	size = ft_lstsize(arg);
	i = -1;
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	while (++i < size)
	{
		ptr[i] = ft_strdup(arg->content);
		arg = arg->right;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	cmd_action(t_node *cur_cmd, char **env_arr, FUNC_TYPE builtin[])
{
	char		*path;
	char		**args;
	int			func_idx;
	struct stat	statbuf;

	args = lst_to_2d_array(cur_cmd);
	func_idx = is_builtin_func(cur_cmd);
	if (func_idx > -1)
		run_builtin(cur_cmd, builtin, func_idx);
	else if (is_absolute_path(cur_cmd->content)
		|| is_relative_path(cur_cmd->content))
	{
		(void)env_arr;
		if (stat(cur_cmd->content, &statbuf) == -1)
			cmd_not_found_error(cur_cmd);
		execve_frame(cur_cmd->content, args, env_arr);
	}
	else
	{
		path = search_path(cur_cmd->content, env_arr);
		if (!path)
			path = no_search_path(cur_cmd, args, cur_cmd->content);
		if (path)
			execve_frame(path, args, env_arr);
	}
}
