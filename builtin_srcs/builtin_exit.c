#include "../minishell.h"

void	print_and_exit(int exit_stat)
{
	printf("exit\n");
	ft_exit(exit_stat);
}

void	if_non_num(void)
{
	printf("minishell: exit: a: numeric argument required\n");
	print_and_exit(255);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

int	cnt_args(char **args)
{
	int	idx;

	idx = 0;
	while (args[idx])
		idx++;
	return (idx);
}

void	builtin_exit(char **args)
{
	int	cnt;

	cnt = cnt_args(args);
	if (cnt == 1)
		print_and_exit(0);
	else if (cnt == 2)
	{
		if (is_numeric(args[1]))
			print_and_exit(ft_atoi(args[1]));
		else
			if_non_num();
	}
	else
	{
		if (is_numeric(args[1]))
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			set_or_get_status(1);
		}
		else
			if_non_num();
	}
}
