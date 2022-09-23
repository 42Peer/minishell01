#include "minishell.h"

/*


else if (cnt == 2)
{
	if (args[1] == 숫자)
	{
		set_or_get(숫자);
		print_and_exit();
	}
	else //
	{
		printf("bash: exit: a: numeric argument required");
		set_or_get(255);
		print_and_exit();
	}
}
else //(args 갯수 3개이상일때)
{
	if (args[1] == 숫자)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments");
		set_or_get(1);
	}
	else
	{
		printf("bash: exit: a: numeric argument required");
		set_or_get(255);
		print_and_exit();
	}
}

*/
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
	exit(0);
}

void	builtin_exit(char **args)
{
	int	cnt;

	cnt = cnt_args(args);
	if (cnt == 1)
		print_and_exit();
	

}