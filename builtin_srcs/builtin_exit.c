#include "../minishell.h"

void	print_and_exit(int exit_stat)
{
	printf("exit\n");
	ft_exit(exit_stat);
}

void	if_non_num(char *args1)
{
	printf("smash: exit: %s: numeric argument required\n", args1);
	print_and_exit(255);
}

int	is_numeric(char *str)
{
	char	*temp;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	temp = (char *)str;
	while (temp[0] == '0' && temp[0] != '\0')
		temp++;
	if (ft_strlen(temp) > 10)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
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
			if_non_num(args[1]);
	}
	else
	{
		if (is_numeric(args[1]))
		{
			printf("exit\n");
			printf("smash: exit: too many arguments\n");
			set_or_get_status(1);
		}
		else
			if_non_num(args[1]);
	}
}
