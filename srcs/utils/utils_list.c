#include "../../minishell.h"

t_token	*ft_lstnew(int type, char *content)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		system_call_error(ALLOC_FAIL);
	new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstiter(t_token *lst, void (*f)(char *))
{
	while (lst)
	{
		printf("type : %d", lst->type);
		printf(" content : ");
		f(lst->content);
		printf("\n");
		lst = lst->next;
	}
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	ft_lstclear(t_token **lst)
{
	t_token	*cur;

	while (*lst)
	{
		cur = *lst;
		cur->type = 0;
		if (cur->content)
			free(cur->content);
		*lst = (*lst)->next;
		cur->next = NULL;
		free(cur);
	}
}

int	ft_lstsize(t_node *lst)
{
	int		count;
	t_node	*ptr;

	if (!lst)
		return (0);
	count = 1;
	ptr = lst;
	while (lst->right)
	{
		lst = lst->right;
		count++;
	}
	lst = ptr;
	return (count);
}
