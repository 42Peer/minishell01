#include "../../minishell.h"

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

void	single_process(t_struct *ds, t_func_type builtin[], int func_idx)
{
	int			old_stdout;
	int			old_stdin;
	int			err;

	old_stdout = 0;
	old_stdin = dup(STDIN_FILENO);
	err = 0;
	if (ds->root_node->left->left)
	{
		old_stdout = dup(STDOUT_FILENO);
		err = redir_action(ds->root_node->left->left, 0);
	}
	if (!err)
		run_builtin(ds->root_node->left->right, builtin, func_idx, old_stdin);
	if (ds->root_node->left->left)
		e_dup2(old_stdout, STDOUT_FILENO);
}

void	execute(t_struct *ds)
{
	int			process_cnt;
	int			func_idx;
	t_func_type	builtin[7];

	format_specifier(builtin);
	func_idx = is_builtin_func(ds->root_node->left->right);
	process_cnt = count_process(ds->root_node);
	if (process_cnt == 1 && func_idx > -1)
		single_process(ds, builtin, func_idx);
	else
		fork_process(ds, process_cnt, builtin);
}
