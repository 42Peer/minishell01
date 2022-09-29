#include "../minishell.h"

int	get_pwd(char *path)
{
	if (getcwd(path, PATH_MAX) == NULL)
	{
		set_or_get_status(errno);
		return (1);
	}
	return (0);
}

int	ft_environ_cmp(char *find_str, char *src_str)
{
	int		ret;
	size_t	len;

	len = ft_strlen(find_str);
	ret = ft_strncmp(find_str, src_str, len);
	if (ret)
		return (1);
	if (src_str[len - 1] == '=')
		return (0);
	if (src_str[len] == 0)
		return (0);
	return (1);
}

int	is_found_str_in_environ(char *str1, char *str2)
{
	int	idx;

	idx = -1;
	while (env_array[++idx])
	{
		if (!ft_environ_cmp(str1, env_array[idx]))
			return (1);
		if (!ft_environ_cmp(str2, env_array[idx]))
			return (1);
	}
	return (0);
}

int	update_str_in_environ(char *export_name, char *path)
{
	char	*args[3];
	char	*export_value;

	export_value = ft_strjoin_no_free(export_name, path);
	args[0] = "export";
	args[1] = export_value;
	args[2] = NULL;
	builtin_export(args);
	free(export_value);
	return (0);
}

void	builtin_cd(char **args)
{
	char		*path;
	char		old_path[PATH_MAX];
	char		new_path[PATH_MAX];

	check_args(args);
	path = args[1];
	if (get_pwd(old_path) < 0)
		return ;
	if (chdir(path))
	{
		builtin_error();
		return ;
	}
	if (get_pwd(new_path) < 0)
		return ;
	if (is_found_str_in_environ("PWD=", "PWD"))
		update_str_in_environ("PWD=", new_path);
	if (is_found_str_in_environ("OLDPWD=", "OLDPWD"))
		update_str_in_environ("OLDPWD=", old_path);
}
