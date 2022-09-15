#include "minishell.h"

char	*delquote(char *str);
char	*save(char *src, char c, int len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
void	tree_parser(t_node *node);
void	ft_traverse(t_node *node);

void	tree_parser(t_node *node)
{
	char	*new_content;

	new_content = NULL;
    if (!(node))
		return ;
	// printf("now node type : %s node content : %s\n", token_str[node->type], node->content);
	tree_parser(node->left);
	tree_parser(node->right);
	if (node->type == T_WORD) 
    {
		new_content = delquote(node->content);
		free(node->content);
		node->content = new_content;
	}
}
