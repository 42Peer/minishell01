#include "minishell.h"

int	last_word_count(char **str)
{
	int	count;

	count = -1;
	while (str[++count]);
	return (count - 1);
}

int	not_newline(char *str)
{
	int	i;
	int	not_newline;

	if (!str)
		return (0);
	i = -1;
	not_newline = 0;
	if (str[++i] == '-') // 첫글자가 - 이면
	{
		while (str[++i] == 'n')
			;
		if (str[i] == '\0')
			not_newline = 1;
	}
	return (not_newline);
}

void	print_str(char **str, int i, int idx_last_word)
{
	if (i != idx_last_word)
		printf("%s ", str[i++]);
	else
		printf("%s", str[i++]);
}

void	builtin_echo(char **args) // 가변으로 받기
{
	int	i;
	int	idx_last_word;
	int	flag;

	idx_last_word = last_word_count(args);
	i = 1;
	flag = not_newline(args[i]);
	if (flag)
		while (not_newline(args[++i]))
			;
	i--;
	if (flag)
		while (args[i] && ++i)
			print_str(args, i, idx_last_word);
	else
	{
		while (args[i] && ++i)
			print_str(args, i, idx_last_word);
		printf("\n");
	}
}

//	if (args[++i][++j] == '-') // 첫글자가 - 이면
//	{
	// while (not_newline(args[i++])) ;
	// j = 0;
	// while (1)
	// {
	// 	if (args[i][j] == '-')
	// 	{
	// 		while (args[i][++j] == 'n') ;
	// 		if (args[i][j] != 'n')
	// 			break ;
	// 	}
	// 	++i;
	// 	j = 0;
	// 	if (args[i][j] != '-')
	// 		break;
	// }

/*
	int i = 1;
	int j = 0;
	
	while (1)
	{
		if (args[i][j]첫 글자가 "-"이면)
		{
			while (args[i][++j] == 'n') ;
			if (args[i][j] != 'n')
				break ;
		}
		++i;
		j = 0;
		if (args[i][j] != '-')
			break;
	}
	
	
	(3)현재글자가 n이 아니면 출력해야한다.
	
	
*/