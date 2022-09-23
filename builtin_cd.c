#include "minishell.h"

void builtin_cd(char **args)
{
	int		ret;
	char	*path;

	path = args[1];
	if (!(args[1]))
		return ;
	ret = chdir(path);
	if (!ret)
	{
		set_or_get_status(errno);
		return ;
	}
}
