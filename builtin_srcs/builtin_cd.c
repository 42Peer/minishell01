#include "../minishell.h"

void builtin_cd(char **args)
{
	int		ret;
	char	*path;

	path = args[1];
	if (!(args[1]))
		return ;
	// if (stat(cur_cmd->content, &statbuf) == -1)
	// 		cmd_not_found_error(cur_cmd);
	ret = chdir(path);
	if (ret)
	{
		builtin_error();
		return ;
	}
}
