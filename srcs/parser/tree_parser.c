#include "../../minishell.h"

static void	cmd_parser(t_node *node)
{
	char	*new_content;

	if (!node)
		return ;
	cmd_parser(node->left);
	cmd_parser(node->right);
	if (node->type == T_WORD)
	{
		new_content = delquote_expand(node->content, NULL);
		free(node->content);
		node->content = new_content;
	}
}

static void	check_invalid_redir_content(t_node *node, int *syntax_errored)
{
	if (ft_strncmp(node->content, ">>", 3) != 0
		&& ft_strncmp(node->content, ">", 2) != 0
		&& ft_strncmp(node->content, "<", 2) != 0
		&& ft_strncmp(node->content, "<<", 3) != 0)
	{
		set_or_get_status(258);
		*syntax_errored = 1;
	}
}

void	redir_deal_quote(t_node *node)
{
	char	*new_content;	
	int		quoted_delimit;

	quoted_delimit = 0;
	new_content = delquote_expand(node->content, &quoted_delimit);
	free(node->content);
	node->content = new_content;
}

static void	redir_parser(t_node *node, int *syntx_erred)
{
	int		quoted_delimit;
	char	*new_content;

	quoted_delimit = 0;
	if (!node || set_or_get_heredoc_status(GET) == CTRL_C)
		return ;
	if (node->type == T_REDIR)
	{
		check_invalid_redir_content(node, syntx_erred);
		if (ft_strncmp(node->content, "<<", 3) == 0)
		{
			new_content = delquote_expand(node->right->content,
					&quoted_delimit);
			free(node->right->content);
			node->type = T_HEREDOC;
			node->right->content = new_content;
			func_heredoc(node, node->right->content, quoted_delimit);
		}
	}
	else if (node->type == T_WORD)
		redir_deal_quote(node);
	redir_parser(node->right, syntx_erred);
	redir_parser(node->left, syntx_erred);
}

int	tree_parser(t_node *node, int *syntx_erred)
{
	if (!(node))
		return (0);
	if (node->type == N_PHRASE)
	{
		if (!node->left && !node->right)
		{
			*syntx_erred = 1;
			set_or_get_status(258);
		}
		redir_parser(node->left, syntx_erred);
		cmd_parser(node->right);
	}
	else
	{
		tree_parser(node->left, syntx_erred);
		tree_parser(node->right, syntx_erred);
	}
	return (0);
}
