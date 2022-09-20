#include "minishell.h"

static int	ft_word_count(char const *str, char c);
static char	**ft_put_array(char **array, char const *str, char c);
static char	**ft_free_array(char **array, int end);


char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_cnt;

	if (s == NULL)
		return (NULL);
	word_cnt = ft_word_count(s, c);
	array = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (array == NULL)
		system_call_error();
	array[word_cnt] = 0;
	array = ft_put_array(array, s, c);
	return (array);
}

static int	ft_word_count(char const *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c)
		{
			++cnt;
			while (*str != c && *str)
				++str;
		}
		while (*str == c && *str)
			++str;
	}
	return (cnt);
}

static char	**ft_put_array(char **array, char const *str, char c)
{
	char	*wd_start;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			wd_start = &(*(char *)str);
			while (*str && *str != c && ++word_len)
				++str;
			array[i] = (char *)malloc(sizeof(char) * (word_len + 1));
			if (array[i] == NULL)
				return (ft_free_array(array, i));
			ft_strlcpy(array[i], wd_start, word_len + 1);
			++i;
			word_len = 0;
		}
		else if (*str == c)
			++str;
	}
	return (array);
}

static char	**ft_free_array(char **array, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}

// void	heredoc_traverse(t_node *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == T_HEREDOC)
// 	{
// 		unlink(node->right->content);
// 		printf("fuck ya%s\n", node->right->content);
// 	}
// 	else
// 	{
// 		heredoc_traverse(node->left);
// 		heredoc_traverse(node->right);
// 	}
// }

// void	heredoc_cleaner(t_struct *ds)
// {
// 	printf("start cleanning\n");
// 	heredoc_traverse(ds->root_node);
// }

int	status_error(int error)
{
	static int status;

	if (error)
		status = error;
	return (status);
}

void	system_call_error(void)
{
	printf("ERROR: system call error!\n");
	exit(errno);
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_HEREDOC)
	{
		printf("!ALERT! unlink target : %s\n", node->right->content);
		unlink(node->right->content);
	}
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
		free(node->content);
	free(node);
}	//후위 순회

void	cleaner(char *str, t_struct *ds, t_token *token)
{
	printf("\n!ALERT! 한 줄 실행 완료. 청소완료!!\n\n");
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
	// if (ds && ds->head_env)
	// {
	// 	env_lstclear(&(ds->head_env));
	// 	ds->head_env = NULL;
	// }
	if (token)
		ft_lstclear(&token);
}

void	clean_exit(int flag, char *str, t_token *token_list, t_struct *ds)	// free도 추가
{
	printf("\n!ALERT! now clean_exit\n\n");
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
	if (ds && ds->head_env)
		env_lstclear(&(ds->head_env));
	if (flag == SUCCESS)
		printf("!ALERT! 정상 종료!\n");
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
	if (ary == NULL)
		system_call_error();
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
		system_call_error();
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
