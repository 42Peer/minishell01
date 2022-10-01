#include "../../minishell.h"

int	set_or_get_heredoc_status(int status)
{
	static int	s_status;

	if (status >= 1)
		s_status = CTRL_C;
	else if (status == 0)
		s_status = 0;
	return (s_status);
}

void	heredoc_sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	close(0);
	set_or_get_heredoc_status(CTRL_C);
	set_or_get_status(1);
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
}

void	here_doc_handler(void)
{
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
