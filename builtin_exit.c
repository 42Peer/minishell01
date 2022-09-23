#include "minishell.h"

/*
- exit
- exit argument
	ㄴ exit 숫자
		ㄴ$?하면 그 숫자가 출력돼야함
		ex1)
			bash-3.2$ exit 0
			exit
			jeanne@gimjiin-ui-MacBookPro ~ % $?  
			zsh: command not found: 0
		ex2)
			bash-3.2$ exit 127
			exit
			jeanne@gimjiin-ui-MacBookPro ~ % $?
			zsh: command not found: 127
	ㄴ exit !숫자 : 메시지 뜨고, 나감
		ex)
			bash-3.2$ exit a
			exit
			bash: exit: a: numeric argument required
			jeanne@gimjiin-ui-MacBookPro ~ % 
- exit argument"s"
	ㄴ exit 숫자 ... : 메시지 뜨고, exit 안됨
		ex)
			bash-3.2$ exit 0 1 2
			exit
			bash: exit: too many arguments
			bash-3.2$
	ㄴ exit 문자 ... : 메세지 뜨고, exit 됨
		ex)
			bash-3.2$ exit a b c
			exit
			bash: exit: a: numeric argument required
			jeanne@gimjiin-ui-MacBookPro ~ %

//if (args 갯수 1개일때)
if (args 갯수 2개일때)
{
	if (args[1] == 숫자)
		()
}
else if (args 갯수 3개이상일때)
()
printf("exit\n");
exit(0);
*/

void	builtin_exit(char **args)
{
	(void)args;
	printf("exit\n");
	exit(0);
}