#include "minishell.h"

char	*delquote(char *str);
char	*save(char *src, char c, size_t len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
void	tree_parser(t_node *node);
void	ft_traverse(t_node *node);

void	tree_parser(t_node *node)
{
	char	*new_content;

	new_content = NULL;
  	printf("content : %s\n", node->content);

    if (!(node))
		return ;
	// printf("now node type : %s node content : %s\n", token_str[node->type], node->content);
	tree_parser(node->left);
	tree_parser(node->right);
	if (node->type == T_WORD) 
    {
		printf("content : %s\n", node->content);
		// node->content = delquote(node->content);
		new_content = delquote(node->content);
		free(node->content);
		node->content = new_content;
		printf("content : %s\n", node->content);
	}
}
