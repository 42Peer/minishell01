#include "../minishell.h"

int	last_word_count(char **str)
{
	int	count;

	count = -1;
	while (str[++count])
		;
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
	if (str[++i] == '-')
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
		write(1, str[i], ft_strlen(str[i]));
	else
		write(1, str[i], ft_strlen(str[i]));
}

void	builtin_echo(char **args)
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
	--i;
	if (flag)
		while (args[++i])
			print_str(args, i, idx_last_word);
	else
	{
		while (args[++i])
			print_str(args, i, idx_last_word);
		printf("\n");
	}
	set_or_get_status(0);
}
