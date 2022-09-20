#include "minishell.h"

void	sigint_handler(int signum)
{
	printf("SIGINT!\n");
}

void	sigquit_handler(int signum)
{
	printf("SIGQUIT!\n");
}

struct termios	old_set;

void	signal_handler(void)
{
	// struct termios	new_set;

	// tcgetattr(0, &old_set);
	// new_set = old_set;
	// new_set.c_iflag &= (~IGNBRK);
	// new_set.c_iflag &= (~BRKINT);
	// new_set.c_lflag &= (~ISIG);
	// new_set.c_cc[VSUSP] = VDISCARD;
	// tcsetattr(0, TCSANOW, &new_set);
	// tcsetattr(0, TCSANOW, &old_set);

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sigint_handler); // ctrl C //
//	 signal(SIGINT, sigint_handle); // ctrl D //
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, sigquit_handler); // ctrl \ //
}
