#ifndef	MINISHELL_H
# define MINISHELL_H

// # include "libft/libft.h"
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
# include <readline/readline.h>	// readline,
# include <readline/history.h>	// rl_on_new_line, rl_replace_line, rl_redisplay, add_history,

# define ERROR		1
# define SUCCESS	0
# define PATH_MAX	1024

typedef void	(*FUNC_TYPE)(char **);
char **check;

typedef enum e_err
{
	ALLOC_FAIL = 12,
	CMD_NOT_FOUND = 127,
}	t_err;

typedef enum e_mode
{
    READ,
    WRITE,
	APPEND,
    END,
    CONTINUE
}	t_mode;


typedef enum e_type
{
	NONE,
	T_WORD,
	T_PIPE,
	T_REDIR,
	T_HEREDOC,
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
	int		sin_quoted;
	int		dou_quoted;
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_struct
{
	t_token	*head_token;
	t_node	*root_node;
	t_env	*head_env;
	char	**env_array;
}	t_struct;

/*
 *						signal handler
 */

void	sigint_handler(int signum);
void	process_handler(int signum);
void	signal_handler(void);
void	in_process_signal_handle(void);

/*
 *						env function
 */

t_env	*env_lstnew(char *env);
void	env_lstadd_back(t_env **lst, t_env *new);
void	make_env_list(char **envp, t_struct *ds);
void	env_lstclear(t_env **lst);
void	env_lstiter(t_env *lst, void (*f)(char *));		// tmp_func

void	make_env_array(char **envp, t_struct *ds);

/*
 *						util function
*/

void	free_tree(t_node *node);
void	cleaner(char *str, t_struct *ds, t_token *token);
void	clean_exit(int error, char *str, t_token *token_list, t_struct *ds);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

void	print_content(char *str);			// tmp func
t_token	*ft_lstnew(int type, char *content);
void	ft_lstiter(t_token *lst, void (*f)(char *));
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);
int	ft_lstsize(t_node *lst);
void	heredoc_cleaner(t_struct *ds);
char	**ft_split(char const *s, char c);

int		set_or_get_status(int error);
void	system_call_error(int error);

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

t_token	*make_redir_node(t_node *cur_process, t_token *cur_token, int *flag);
t_token	*make_cmd_node(t_node *cur_process, t_token *cur_token);
t_token	*make_pipe_node(t_node **cur_process, t_token *cur_token);
t_node	*make_dummy_node(void);
int		make_tree(t_struct *ds);

/*
 *						part III quote & expand & here_doc
*/

size_t	ft_strlen(char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_no_free(char *s1, char *s2);
void	free_2d(char **str);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*save(char *src, char c, size_t len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
int		is_expandable(char *str, int i);
char	*reset_cursor(char *str, int quote_i, int env_i, int *origin_i);
char	*single_quote(char *str, int *quote_i, int *quoted);	// '를 만났을 때, ' 인덱스(i)부터 들어옴
char	*double_quote(char *str, int *quote_i, int *quoted);		// quote_i는 " 위치.
char	*delquote(char *str, int *quoted);
char	*dollar_sign(char *str, int *env_i);

char	**func_heredoc(t_node *node, char *delimiter, int quoted);
void	cmd_parser(t_node *node);
void	redir_parser(t_node *node, int *flag);
int		tree_parser(t_node *node, int *flag);

/*
 *						part IV execute
*/

int		count_process(t_node *node);
int		is_builtin_func(t_node *node);
void	fork_process(t_struct *ds, int cnt);
void	execute(t_struct *ds);

void	cmd_action(t_node *cur_cmd, t_env *env_lst, char **env_arr);

/*
 *						part V built-in
*/

void	builtin_pwd(char **args);
void	builtin_echo(char **args);
int	not_newilne(char **str, int idx_last_word);
int	last_word_count(char **str);
void builtin_cd(char **args);

/*
 *						test function
*/
void	ft_exit(int error);

void	ft_traverse(t_node *node);

// if REDIR
// 	redir;
// else if WORD
// 	execve;
// else if PIPE
// 	fork;

#endif