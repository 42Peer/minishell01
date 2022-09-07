// main 문에서 make_tree 어떻게 되어있는지
// root = make_tree(head_token); // 토큰을 자료구조에 넣는다

#include "minishell.h"

t_token	*make_redir_node(t_node *cur_process, t_token *cur_token)
{
	t_node 	*io_redir;
	t_node	*cur_node;
	t_node	*new_node;
	int		i;

	io_redir = ft_calloc(1, sizeof(t_node));
	io_redir->type = N_REDIR;	
	cur_node = cur_process->left;
	while (cur_node->left)
		cur_node = cur_node->left;
	cur_node->left = io_redir;
	cur_node = cur_node->left;
	i = -1;
	while (++i < 2)
	{
		new_node = ft_calloc(1, sizeof(t_node));
		cur_node->right = new_node;
		new_node->type = cur_token->type;
		new_node->content = cur_token->content;
		cur_token = cur_token->next;
		cur_node = cur_node->right;
	}
	return (cur_token);
}

t_token	*make_cmd_node(t_node *cur_process, t_token *cur_token)
{
	t_node *cur_node;
	t_node *cmd_node;

	cur_node = cur_process->left;
	while (cur_node->right)
		cur_node = cur_node->right;
	cmd_node = ft_calloc(1, sizeof(t_node));
	cur_node->right = cmd_node;
	cmd_node->type = cur_token->type;
	cmd_node->content = cur_token->content;
	return (cur_token->next);
}

t_token *make_pipe_node(t_node **cur_process, t_token *cur_token)
{
	(*cur_process)->right = make_dummy_node();
	*cur_process = (*cur_process)->right;
	return (cur_token->next);
}

t_node *make_dummy_node(void)
{
	t_node	*process;
	t_node	*phrase;

	process = ft_calloc(1, sizeof(t_node));
	process->type = N_PROCESS;
	phrase = ft_calloc(1, sizeof(t_node));
	phrase->type = N_PHRASE;
	process->left = phrase;
	return (process);
}

t_node	*make_tree(t_token *head_token)
{
	t_node	*root;
	t_node	*cur_process;
	t_token *cur_token;

	root = make_dummy_node();
	cur_token = head_token;
	cur_process = root;
	while (cur_token)
	{
		if (cur_token->type == T_REDIR)
			cur_token = make_redir_node(cur_process, cur_token);
		else if (cur_token->type == T_PIPE)
			cur_token = make_pipe_node(&cur_process, cur_token);
		else if (cur_token->type == T_WORD)
			cur_token = make_cmd_node(cur_process, cur_token);
		else
			printf("make_tree ERROR!!!!\n");
	}
	return (root);
}
