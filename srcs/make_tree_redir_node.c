#include "../minishell.h"

void	make_io_redir_node(t_node **io_redir)
{
	*io_redir = ft_calloc(1, sizeof(t_node));
	if (!(*io_redir))
		system_call_error(ALLOC_FAIL);
	(*io_redir)->type = N_REDIR;
}

t_node	*attach_node_to_tree(t_node *cur_node, t_node *io_redir)
{
	while (cur_node->left)
		cur_node = cur_node->left;
	cur_node->left = io_redir;
	cur_node = cur_node->left;
	return (cur_node);
}

void	make_io_redir_child_node(t_node *cur_node, t_node **new_node)
{
	*new_node = ft_calloc(1, sizeof(t_node));
	if (!(*new_node))
		system_call_error(ALLOC_FAIL);
	cur_node->right = *new_node;
}

void	make_io_redir_chile_node_content(
	t_node *new_node, t_token **cur_token, t_node **cur_node)
{
	new_node->content = ft_strdup((*cur_token)->content);
	*cur_token = (*cur_token)->next;
	*cur_node = (*cur_node)->right;
}

t_token	*make_redir_node(t_node *cur_process, t_token *cur_token, int *flag)
{
	t_node	*io_redir;
	t_node	*cur_node;
	t_node	*new_node;
	int		i;

	make_io_redir_node(&io_redir);
	cur_node = cur_process->left;
	cur_node = attach_node_to_tree(cur_node, io_redir);
	i = -1;
	while (++i < 2)
	{
		make_io_redir_child_node(cur_node, &new_node);
		if (!cur_token)
		{
			printf("Error: syntax error!\n");
			set_or_get_status(258);
			*flag = 1;
			break ;
		}
		else
			new_node->type = cur_token->type;
		make_io_redir_chile_node_content(new_node, &cur_token, &cur_node);
	}
	return (cur_token);
}
