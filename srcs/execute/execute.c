#include "../../minishell.h"

void	run_builtin(t_node *cur_cmd, FUNC_TYPE builtin[],
	int func, int old_stdin)
{
	char	*cmd;
	char	**args;

	args = lst_to_2d_array(cur_cmd);
	cmd = ft_strdup(cur_cmd->content);
	builtin[func](args);
	dup_frame(old_stdin, STDIN_FILENO);
	close(old_stdin);
	free(cmd);
	free_2d(args);
}

int	count_process(t_node *node)
{
	int	cnt;

	cnt = 1;
	while (node->right)
	{
		++cnt;
		node = node->right;
	}
	return (cnt);
}

int	is_builtin_func(t_node *cmd)
{
	int	func;

	func = -1;
	if (cmd && cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->content, "echo", 5))
			func = 0;
		else if (!ft_strncmp(cmd->content, "cd", 3))
			func = 1;
		else if (!ft_strncmp(cmd->content, "pwd", 4))
			func = 2;
		else if (!ft_strncmp(cmd->content, "export", 7))
			func = 3;
		else if (!ft_strncmp(cmd->content, "unset", 6))
			func = 4;
		else if (!ft_strncmp(cmd->content, "env", 4))
			func = 5;
		else if (!ft_strncmp(cmd->content, "exit", 5))
			func = 6;
	}
	return (func);
}

void	format_specifier(void (*f[])(char **))
{
	f[0] = builtin_echo;
	f[1] = builtin_cd;
	f[2] = builtin_pwd;
	f[3] = builtin_export;
	f[4] = builtin_unset;
	f[5] = builtin_env;
	f[6] = builtin_exit;
}

void	execute(t_struct *ds)
{
	int			process_cnt;
	int			func_idx;
	FUNC_TYPE	builtin[7];
	int			old_stdout;
	int			old_stdin;

	format_specifier(builtin);
	func_idx = is_builtin_func(ds->root_node->left->right);
	process_cnt = count_process(ds->root_node);
	old_stdout = 0;
	old_stdin = dup(STDIN_FILENO);
	if (process_cnt == 1 && func_idx > -1)
	{
		if (ds->root_node->left->left)
		{
			old_stdout = dup(STDOUT_FILENO);
			redir_action(ds->root_node->left->left);
		}
		run_builtin(ds->root_node->left->right, builtin, func_idx, old_stdin);
		if (ds->root_node->left->left)
			dup_frame(old_stdout, STDOUT_FILENO);
	}
	else
		fork_process(ds, process_cnt, builtin);
}
