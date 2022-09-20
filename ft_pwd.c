#include "minishell.h"

void	ft_pwd(void)
{
	// char *getcwd(char *buf, size_t size);
	char *path;
	char path[1024];//크기 어떻게?

	getcwd(path, 1024);
	printf("working directory : %s\n", path);
	set_or_get_status(0);
}
// 	path = PATH찾기.
//pwd 다음에 오는 word는 다 문자 처리. ex) '