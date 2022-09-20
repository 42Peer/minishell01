#include "minishell.h"

void	ft_pwd(char **cmd)
{
	(void)cmd;
	printf("pwd\n");
	// char *getcwd(char *buf, size_t size);
	// char *path;
	// char path[1024]; //크기 어떻게?

	// if (getcwd(path, 1024) == NULL);
	// {
	// 	set_or_get_status(errno);
	// 	return ;
	// }
	// printf("working directory : %s\n", path);
	// set_or_get_status(0);
}
// 	path = PATH찾기.
//pwd 다음에 오는 word는 다 문자 처리. ex) '