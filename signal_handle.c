#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	process_handler(int signum)
{
	if (signum == SIGINT)
		exit(130);
	else
		exit(131);
}

void	signal_handler(void)
{
//	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sigint_handler); // ctrl C //
//	 signal(SIGINT, sigint_handle); // ctrl D //
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGQUIT, sigquit_handler); // ctrl \ //
}// 

void	in_process_signal_handle(void)
{
	signal(SIGINT, process_handler);
	signal(SIGQUIT, process_handler);
}