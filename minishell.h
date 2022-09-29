#ifndef	MINISHELL_H
# define MINISHELL_H

// # include "libft/libft.h"
# include <stdio.h>				// printf,
# include <stdlib.h>			// malloc, free, exit, getenv,
# include <unistd.h>			// write, close, fork, getcwd, unlink, execve, dup, dup2, pipe, chdir, isatty, ttyname, ttyslot,
# include <fcntl.h>				// open,
# include <sys/wait.h>			// wait, waitpid, wait3, wait4,
# include <signal.h>			// signal, kill,
# include <dirent.h>			// opendir, readdir, closedir,
# include <sys/types.h>			//
# include <sys/stat.h>			// stat, lstat, fstat,
# include <string.h>			// strerror,
# include <errno.h>				// errno,
# include <sys/ioctl.h>			// ioctl,
# include <termios.h>			// tcsetattr, tcgetattr,
# include <term.h>				// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>	// readline,
# include <readline/history.h>	// rl_on_new_line, rl_replace_line, rl_redisplay, add_history,
# include <limits.h>

# define ERROR		1
# define SUCCESS	0
//# define PATH_MAX	1024

typedef void	(*FUNC_TYPE)(char **);
char **env_array;

typedef enum e_err
{
	SUCCESS_EXECUTE = 0,
	GENERAL_ERROR = 1,
	ALLOC_FAIL = 12,
	EXEC_FILE_FAIL = 126,//execve == -1 && errno~
	CMD_NOT_FOUND = 127,
	SYNTAX_ERROR = 258,
	SIG_INT = 130,//sigint
	SIG_QUIT = 131//sigquit
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

typedef struct s_quote_idx
{
	int	env;
	int	cur;
}	t_quote_idx;

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
}	t_struct;

/*
 *						signal handler
 */

void	sigint_handler(int signum);
void	process_handler(int signum);
void	signal_handler(void);
void	in_process_signal_handler(void);

/*
 *						env function
 */

t_env	*env_lstnew(char *env);
void	env_lstadd_back(t_env **lst, t_env *new);
void	make_env_list(char **envp, t_struct *ds);
void	env_lstclear(t_env **lst);
void	env_lstiter(t_env *lst, void (*f)(char *));		// tmp_func

void	make_env_array(char **envp);

/*
 *						util function
*/

void	free_2d(char **str);
void	free_tree(t_node *node);
void	cleaner(char *str, t_struct *ds, t_token *token);
void	clean_exit(int error, char *str, t_token *token_list, t_struct *ds);

void	ft_exit(int error);
int		set_or_get_status(int error);
void	cmd_not_found_error(t_node *cmd);
void	system_call_error(int error);
void	builtin_error(void);

t_token	*ft_lstnew(int type, char *content);
void	ft_lstiter(t_token *lst, void (*f)(char *));
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);
int		ft_lstsize(t_node *lst);

// libft_utils_1~n.c
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);

size_t	ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_no_free(char *s1, char *s2);
int		ft_isalnum(int c);
void	print_content(char *str);			// tmp func
void	check_args(char **args);


/*
 *						part I tokenize.c
*/

int		is_operator(char c);
int		is_whitespace(char c);
int		is_quote(char c);

void	case_part_of_operator(char *str, t_token_info *info);
void	case_quote_start(char chr, t_token_info *info);
void	case_operator(char *str, t_token_info *info);
void	case_blank(char *str, t_token_info *info);
void	case_part_of_word(char *str, t_token_info *info);
void	case_new_word(t_token_info *info);
int		is_case_unquoted(t_token_info *info);

void	info_init(t_token_info *info);
int		make_token(char *str, int copy_idx, t_token_info *info);
void	token_search(char *str, t_token_info *info);
t_token	*tokenize(char *str);

/*
 *						part II make_tree.c
*/

t_token	*make_redir_node(t_node *cur_process, t_token *cur_token, int *flag);
t_token	*make_cmd_node(t_node *cur_process, t_token *cur_token);
t_token	*make_pipe_node(t_node **cur_process, t_token *cur_token);
t_node	*make_dummy_node(void);
int		make_tree(t_struct *ds);

/*
 *						part III quote & expand & here_doc
*/

int		is_expandable(char *str, int i);
char	*ft_getenv(char *key);
char	*save(char *src, char c, size_t len);

char	*dollar_sign(char *str, int *cur);
char	*single_quote(char *str, int *quote_i, int *quoted_delimit);
char	*double_quote(char *str, int *quote_i, int *quoted_delimit);
char	*delquote_expand(char *str, int *quoted_delimit);

char	**func_heredoc(t_node *node, char *delimiter, int quoted_delimit);
int		tree_parser(t_node *node, int *flag);

/*
 *						part IV execute
*/

int		count_process(t_node *node);
int		is_builtin_func(t_node *node);
void	child_process(t_node *cur_phrase, char **env_arr, FUNC_TYPE builtin[]);
void	fork_process(t_struct *ds, int cnt, FUNC_TYPE builtin[]);
void	run_builtin(t_node *cur_cmd, FUNC_TYPE builtin[], int func, int old_stdin);
void	execute(t_struct *ds);
void	cmd_action(t_node *cur_cmd, char **env_arr, FUNC_TYPE builtin[], int old_stdin);
void	cmd_action_init(t_node *cur_cmd, char ***p_args, int *p_func_idx);
void	redir_action(t_node *cur_redir);
char	**lst_to_2d_array(t_node *arg);
void	dup_frame(int fd, int std);
int		is_absolute_path(char *path);
int		is_relative_path(char *path);
char	*search_path(char *cmd, char **env_arr);
void	open_redir_file(char *file, int mode);




/*
 *						func_frame
*/

void	fork_frame(t_node **cur_process, FUNC_TYPE builtin[]);
void	execve_frame(char *path, char **args, char **env_arr);
char	*no_search_path(t_node *cur_cmd, char **args, char *cmd);

/*
 *						part V built-in
*/

void	builtin_pwd(char **args);
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_env(char **args);
int		builtin_arg_count(char **args);
void	builtin_export(char **args);
void	builtin_unset(char **args);
void	builtin_exit(char **args);

/*
 *						test function
*/

void	ft_traverse(t_node *node);

/*
builtin_exit
*/
void	print_and_exit(int exit_stat);
int		ft_atoi(const char *str);


#endif
