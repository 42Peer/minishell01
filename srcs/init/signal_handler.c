#include "../../minishell.h"

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
	{
		printf("\n");
		rl_redisplay();
	}
	else
		exit(SIG_QUIT);
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	in_process_signal_handler(void)
{
	signal(SIGINT, process_handler);
	signal(SIGQUIT, process_handler);
}
