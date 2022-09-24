#include "../minishell.h"
//정상종료시 다 free 해줘야될것같은데
void	if_non_num(void)
{
	printf("minishell: exit: a: numeric argument required\n");
	// set_or_get_status(255);
	print_and_exit();
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
	while(args[idx])
	{
		idx++;
	}
	return (idx);
}

void	print_and_exit(void)
{
	printf("exit\n");
	ft_exit(SUCCESS_EXECUTE);
}

void	builtin_exit(char **args)
{
	int	cnt;
	// int	num;

	cnt = cnt_args(args);
	// num = 0;
	if (cnt == 1)
		print_and_exit();
	else if (cnt == 2)
	{
		if (is_numeric(args[1]))
		{
			
			// ft_atoi(args[1]);
			// num = ft_atoi(args[1]);
			// set_or_get_status(num);
			print_and_exit();
		}
		else
		{
			if_non_num();
		}
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
		{
			if_non_num();
		}
	}
}