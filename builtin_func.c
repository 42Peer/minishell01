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
