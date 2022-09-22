#include "minishell.h"

int	last_word_count(char **str)
{
	int	count;

	count = -1;
	while (str[++count]);
	return (count - 1);
}

void	builtin_echo(char **args) // 가변으로 받기
{
	int	i;
	int	j;
	int	idx_last_word;

	i = 0;
	j = -1;
	idx_last_word = last_word_count(args);
	printf("start\n");
	if (args[++i][++j] == '-') // 첫글자가 - 이면
	{
	printf("if\n");

		while (args[i][++j] == 'n') // -n 찾는과정
			;
		if (args[i][j] == '\0') 
		{
			while (args[++i])
			{
				if (i != idx_last_word)
					printf("%s ", args[i]);
				else
					printf("%s", args[i]);
			}
		}
		else
		{
			while (args[i])
			{
				if (i != idx_last_word)
					printf("%s ", args[i++]);
				else
					printf("%s\n", args[i++]);
			}
		}
	}
	else
	{
	printf("01\n");
		while (args[i])
		{
	printf("02\n");
			if (i != idx_last_word)
				printf("%s ", args[i++]);
			else
				printf("%s\n", args[i++]);
		}
	}
}
