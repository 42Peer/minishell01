#include "../../minishell.h"

void	free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_HEREDOC)
		unlink(node->right->content);
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
		free(node->content);
	free(node);
}

void	cleaner(char *str, t_head *p_head, t_token *token)
{
	if (str)
		free(str);
	if (p_head && p_head->node)
	{
		free_tree(p_head->node);
		p_head->node = NULL;
	}
	if (p_head && p_head->token)
	{
		ft_lstclear(&(p_head->token));
		p_head->token = NULL;
	}
	if (token)
		ft_lstclear(&token);
}

void	clean_exit(int flag, char *str, t_token *token_list, t_head *p_head)
{
	printf("\n!ALERT! now clean_exit\n\n");
	if (str)
		free(str);
	if (token_list)
		ft_lstclear(&(token_list));
	if (p_head && p_head->node)
		free_tree(p_head->node);
	if (p_head && p_head->token)
		ft_lstclear(&(p_head->token));
	if (flag == SUCCESS)
		printf("!ALERT! 정상 종료!\n");
	exit (flag);
}
