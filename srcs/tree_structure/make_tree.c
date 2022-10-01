#include "../../minishell.h"

t_token	*make_cmd_node(t_node *cur_process, t_token *cur_token)
{
	t_node	*cur_node;
	t_node	*cmd_node;

	cur_node = cur_process->left;
	while (cur_node->right)
		cur_node = cur_node->right;
	cmd_node = ft_calloc(1, sizeof(t_node));
	if (!cmd_node)
		system_call_error(ALLOC_FAIL);
	cur_node->right = cmd_node;
	cmd_node->type = cur_token->type;
	cmd_node->content = ft_strdup(cur_token->content);
	return (cur_token->next);
}

t_token	*make_pipe_node(t_node **cur_process, t_token *cur_token)
{
	(*cur_process)->right = make_dummy_node();
	*cur_process = (*cur_process)->right;
	return (cur_token->next);
}

t_node	*make_dummy_node(void)
{
	t_node	*process;
	t_node	*phrase;

	process = ft_calloc(1, sizeof(t_node));
	if (!process)
		system_call_error(ALLOC_FAIL);
	process->type = N_PROCESS;
	phrase = ft_calloc(1, sizeof(t_node));
	if (!phrase)
		system_call_error(ALLOC_FAIL);
	phrase->type = N_PHRASE;
	process->left = phrase;
	return (process);
}

int	make_tree(t_struct *ds)
{
	t_node		*cur_process;
	t_token		*cur_token;
	int			syntx_erred;

	here_doc_handler();
	ds->root_node = make_dummy_node();
	cur_token = ds->head_token;
	cur_process = ds->root_node;
	syntx_erred = 0;
	while (cur_token)
	{
		if (cur_token->type == T_REDIR)
			cur_token = make_redir_node(cur_process, cur_token, &syntx_erred);
		else if (cur_token->type == T_PIPE)
			cur_token = make_pipe_node(&cur_process, cur_token);
		else if (cur_token->type == T_WORD)
			cur_token = make_cmd_node(cur_process, cur_token);
		else
			printf("make_tree() ERROR!!!!\n");
		if (syntx_erred == 1)
			return (ERROR);
	}
	return (SUCCESS);
}
