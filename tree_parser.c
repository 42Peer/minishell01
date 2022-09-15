#include "minishell.h"

char	*save(char *src, char c, size_t len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
void	tree_parser(t_node *node);
void	ft_traverse(t_node *node);


void	cmd_parser(t_node *node)
{
	char	*new_content;

	if (!node)
		return ;
	cmd_parser(node->left);
	cmd_parser(node->right);
	if (node->type == T_WORD)
	{
		// node->content = delquote(node->content);
		new_content = delquote(node->content, NULL);
		free(node->content);
		node->content = new_content;
	}
}

void	redir_parser(t_node *node)
{
	int	quoted;

	quoted = 0;		// 기본 0 = 인용 없음 으로 초기화
	if (!node)
		return ;
	if (node->type == T_REDIR)
	{
		if (strcmp(node->content, "<<") == 0)	// heredoc이면
		{
			printf("heredoc 도착!\n");
			printf("delimiter : %s\n", node->right->content);
			node->right->content = delquote(node->right->content, &quoted);
			if (quoted == 0)
				// func_heredoc(quoted);
				printf("인용 없음. 확장 해도 됨.");
			else
				printf("인용 있음. 확장 하면 안됨.");
		}
	}
	else
	{
		redir_parser(node->right);	// T_REDIR
		redir_parser(node->left);	// 다른 redir
	}
}

void	tree_parser(t_node *node)
{
	if (!(node))
		return ;
	// printf("now node type : %s node content : %s\n", token_str[node->type], node->content);
	if (node->type == N_PHRASE)
	{
		redir_parser(node->left);
		cmd_parser(node->right);
	}
	else
	{
		tree_parser(node->left);	// phrase
		tree_parser(node->right);	// 새 프로세스
	}
}