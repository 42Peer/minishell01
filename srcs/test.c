#include "../minishell.h"

char *token_str[8]
	= {"NONE", "T_WORD", "T_PIPE", "T_REDIR", "T_HEREDOC", "N_REDIR",
	"N_PHRASE", "N_PROCESS"};

void	ft_traverse(t_node *node)
{
	if (!(node))
		return ;
	if (node)
		printf("current node->type : [%s]\n", token_str[node->type]);
	if (node->content)
		printf("current node->content : [%s]\n", node->content);
	printf("before move\n");
	ft_traverse(node->left);
	ft_traverse(node->right);
}
