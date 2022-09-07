#ifndef	MINISHELL_H
# define MINISHELL_H
// # include <readline/readline.h>
// # include <stdio.h>
// # include <stdlib.h>
//# include <string.h> //strcmp용 임시 헤더
// # include "libft/libft.h"

# include <readline/readline.h>	// readline, 
# include <readline/history.h>	// rl_on_new_line, rl_replace_line, rl_redisplay, add_history, 
# include <stdio.h>		// printf, 
# include <stdlib.h>		// malloc, free, exit, getenv, 
# include <unistd.h>		// write, close, fork, getcwd, unlink, execve, dup, dup2, pipe, chdir, isatty, ttyname, ttyslot, 
# include <fcntl.h>		// open, 
# include <sys/wait.h>		// wait, waitpid, wait3, wait4, 
# include <signal.h>		// signal, kill, 
# include <dirent.h>		// opendir, readdir, closedir, 
# include <sys/types.h>		// 
# include <sys/stat.h>		// stat, lstat, fstat, 
# include <string.h>		// strerror, 
# include <errno.h>		// errno, 
# include <sys/ioctl.h>		// ioctl, 
# include <termios.h>		// tcsetattr, tcgetattr, 
# include <term.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define ERROR -1

typedef enum e_type
{
	NONE,
	T_WORD,
	T_PIPE,
	T_REDIR,
	N_REDIR,
	N_PHRASE, // pipe 있을 경우 필요함.
	N_PROCESS
}	t_type;

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_token_info
{
	int		start_idx;
	int		cur_idx;
	int		quoted_flag;
	t_type	token_type;
	t_token *p_token_list;
}	t_token_info;

typedef struct s_node
{ // T_WORD, T_PIPE, T_REDIR, N_REDIR, N_PHRASE, N_PROCESS
	int				type;
	t_token			*p_token;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

/*
순회(node)
{
	순회(node->left)
	순회(node->right)
	return (0);
}
*/
// if REDIR
// 	redir;
// else if WORD
// 	execve;
// else if PIPE
// 	fork;

#endif