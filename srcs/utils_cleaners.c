#include "../minishell.h"

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

void	cleaner(char *str, t_struct *ds, t_token *token)
{
	if (str)
		free(str);
	if (ds && ds->root_node)
	{
		free_tree(ds->root_node);
		ds->root_node = NULL;
	}
	if (ds && ds->head_token)
	{
		ft_lstclear(&(ds->head_token));
		ds->head_token = NULL;
	}
	if (token)
		ft_lstclear(&token);
}

void	clean_exit(int flag, char *str, t_token *token_list, t_struct *ds)
{
	printf("\n!ALERT! now clean_exit\n\n");
	if (str)
		free(str);
	if (token_list)
		ft_lstclear(&(token_list));
	if (ds && ds->root_node)
		free_tree(ds->root_node);
	if (ds && ds->head_token)
		ft_lstclear(&(ds->head_token));
	if (flag == SUCCESS)
		printf("!ALERT! 정상 종료!\n");
	exit (flag);
}
