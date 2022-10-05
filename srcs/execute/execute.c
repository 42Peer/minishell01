#include "../../minishell.h"

void	run_builtin(t_node *cur_cmd, t_func_type builtin[], int func)
{
	char	**args;

	args = lst_to_2d_array(cur_cmd);
	builtin[func](args);
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

void	execute(t_head *p_head)
{
	int			process_cnt;
	int			func_idx;
	t_func_type	builtin[7];

	in_process_signal_handler();
	format_specifier(builtin);
	func_idx = is_builtin_func(p_head->node->left->right);
	process_cnt = count_process(p_head->node);
	if (process_cnt == 1 && func_idx > -1)
		exec_builtin(p_head, func_idx, builtin);
	else
		fork_process(p_head, process_cnt, builtin);
}
