#ifndef	MINISHELL_H
# define MINISHELL_H

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

# define ERROR		1
# define SUCCESS	0

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
	t_token *token_list;
}	t_token_info;

typedef struct s_node
{ // T_WORD, T_PIPE, T_REDIR, N_REDIR, N_PHRASE, N_PROCESS
	int				type;
	char			*content;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_struct
{
	t_token	*head_token;
	t_node	*root_node;
}	t_struct;

/*
 *						util function
*/

void	free_tree(t_node *node);
void	clean_exit(int error, char *str, t_token *token_list, t_struct *ds);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

void	print_content(char *str);			// tmp func
t_token	*ft_lstnew(int type, char *content);
void	ft_lstiter(t_token *lst, void (*f)(char *));
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);

/*
 *						part I tokenize
*/

int		is_operator(char c);
int		is_whitespace(char c);
int		is_quote(char c);
int		make_token(char *str, int copy_idx, t_token_info *info);
t_token	*tokenize(char *str);

/*
 *						part II make_tree
*/

t_token	*make_redir_node(t_node *cur_process, t_token *cur_token, t_struct *ds);
t_token	*make_cmd_node(t_node *cur_process, t_token *cur_token, t_struct *ds);
t_token	*make_pipe_node(t_node **cur_process, t_token *cur_token, t_struct *ds);
t_node	*make_dummy_node(t_struct *ds);
void	make_tree(t_struct *ds);

/*
 *						part III quote & expand & here_doc
*/



/*
 *						test function
*/

void	ft_traverse(t_node *node);

// if REDIR
// 	redir;
// else if WORD
// 	execve;
// else if PIPE
// 	fork;

#endif