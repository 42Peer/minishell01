#include "minishell.h"

char *token_str[7]
	= {"NONE", "T_WORD", "T_PIPE", "T_REDIR", "N_REDIR",
	"N_PHRASE", "N_PROCESS"};

void	ft_traverse(t_node *node)
{
	if (!(node))
		return ;
	if (node->content)
		printf("now node type : <%s> | content : <%s>\n", token_str[node->type], node->content);
	ft_traverse(node->left);
	ft_traverse(node->right);
}
