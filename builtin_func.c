#include "minishell.h"

void	echo(char **str) // 가변으로 받기
{
	int	i;

	i = -1;
	if (str[0][++i] == '-')
	{
		while (str[0][++i] == 'n');	// ???? -nnnnnnnnnnnnabc
		if (str[0][i] == '\0') // -n 옵션이 있을 때
		{
			int j = -1;
			while (str[++j])
			{
				if (j != max)
					printf("%s ", str[j]);
				else
					printf("%s", str[j]);
			}		
		}
		else
		{
			int j = -1;
			while (str[++j])
				if (j != max)
					printf("%s", str[j]);
			printf("\n");
		}
	}
	else
	{
		str 들 이어 붙이기.
		printf("%s\n", str);
	}
}

void	pwd(void)//getcwd
{
	// char *getcwd(char *buf, size_t size);
	char *path;
	char path[1024];//크기 어떻게?

	getcwd(path, 1024);
	printf("working directory : %s\n", path);
}
// 	path = PATH찾기.
//pwd 다음에 오는 word는 다 문자 처리. ex) '