#include "minishell.h"

char	*delquote(char *str);
char	*save(char *src, char c, size_t len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
void	tree_parser(t_node *node);
void	ft_traverse(t_node *node);

char *token_str[7]
	= {"NONE", "T_WORD", "T_PIPE", "T_REDIR", "N_REDIR",
	"N_PHRASE", "N_PROCESS"};

void	ft_traverse(t_node *node)
{
	if (!(node))
		return ;
	printf("now node type : %s node content : %s\n", token_str[node->type], node->content);
	ft_traverse(node->left);
	ft_traverse(node->right);
}
