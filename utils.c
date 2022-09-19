#include "minishell.h"

void	heredoc_traverse(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_HEREDOC)
	{
		unlink(node->right->content);
		printf("fuck ya%s\n", node->right->content);
	}
	else
	{
		heredoc_traverse(node->left);
		heredoc_traverse(node->right);
	}
}

void	heredoc_cleaner(t_struct *ds)
{
	printf("start cleanning\n");
	heredoc_traverse(ds->root_node);
}

void	get_error(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
		free(node->content);
	free(node);
}	//후위 순회

void	cleaner(char *str, t_struct *ds, t_token *token)
{
	printf("\n한 줄 실행 완료. 청소완료!!\n\n");
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

void	clean_exit(int flag, char *str, t_token *token_list, t_struct *ds)	// free도 추가
{
	printf("\nnow clean_exit\n\n");
	/* 토크나이즈단계일때 */
	if (str)
		free(str);
	if (token_list)
		ft_lstclear(&(token_list));
	/* 트리단계일때 */
	if (ds && ds->root_node)
		free_tree(ds->root_node);
	if (ds && ds->head_token)
		ft_lstclear(&(ds->head_token));
	if (flag == SUCCESS)
		printf("정상 종료!\n");
	/* 실행 단계 
	if (flag == no)
		printf syntax error;
	else if (flag == CMDNF)
		printf command not found;
	*/
	exit (flag);	//error
}//when do exit, message by strerror()

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr++ = 0;
		--n;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ary;

	ary = malloc(count * size);
	if (ary == 0)
		return (NULL);
	ft_bzero(ary, count * size);
	return (ary);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (!dst && !src)
		return (NULL);
	dst_ptr = dst;
	src_ptr = (unsigned char *)src;
	while (n > 0)
	{
		*dst_ptr++ = *src_ptr++;
		--n;
	}
	return (dst);
}

t_token	*ft_lstnew(int type, char *content)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	print_content(char *str)
{
	printf("token > %s\n", str);
}

void	ft_lstiter(t_token *lst, void (*f)(char *))
{
	while (lst)
	{
		f(lst->content);
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
		cur->type = 0;//NONE
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
