#include "../../minishell.h"

int	exec_builtin(t_struct *ds, int func_idx, t_func_type *builtin)
{
	int	old_stdout;
	int	old_stdin;
	int	redir_erred;
	int	b_child_process;

	redir_erred = 0;
	old_stdin = dup(STDIN_FILENO);
	if (ds->root_node->left->left)
	{
		old_stdout = dup(STDOUT_FILENO);
		b_child_process = 0;
		redir_action(ds->root_node->left->left, b_child_process, &redir_erred);
	}
	if (redir_erred == 0)
		run_builtin(ds->root_node->left->right, builtin, func_idx);
	e_dup2(old_stdin, STDIN_FILENO);
	if (ds->root_node->left->left)
		e_dup2(old_stdout, STDOUT_FILENO);
	return (redir_erred);
}
