#include "../minishell.h"

void	builtin_pwd(char **args)
{
	(void)args;
	char path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
	{
		set_or_get_status(errno);
		return ;
	}
	printf("%s\n", path);
	set_or_get_status(0);
}
// 	path = PATH찾기.
//pwd 다음에 오는 word는 다 문자 처리. ex) '