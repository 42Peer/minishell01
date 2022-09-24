#include "minishell.h"

static int	ft_word_count(char const *str, char c);
static char	**ft_put_array(char **array, char const *str, char c);
static char	**ft_free_array(char **array, int end);
static int	ft_sign_check(const char *str);
static int	ft_is_positive(int n);
static int	ft_count_digit(long n, int sign);

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		sign;
	int		digit;

	sign = ft_is_positive(n);
	nb = n;
	if (n < 0)
		nb = -nb;
	digit = ft_count_digit(nb, sign);
	str = (char *)malloc(sizeof(char) * digit + 1);
	if (str == NULL)
		return (NULL);
	if (sign == -1)
		str[0] = '-';
	str[digit] = 0;
	while (nb > 9)
	{
		str[digit-- - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	str[digit - 1] = nb + '0';
	return (str);
}

static int	ft_is_positive(int n)
{
	if (n >= 0)
		return (1);
	else
		return (-1);
}

static int	ft_count_digit(long n, int sign)
{
	int	cnt;

	cnt = 1;
	if (sign < 0)
		++cnt;
	while (n > 9)
	{
		n = n / 10;
		++cnt;
	}
	return (cnt);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (4);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;
	int		sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		++i;
	if (str[i] == '+' || str[i] == '-')
		sign = ft_sign_check(&str[i++]);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (sign == 1 && ((nb > LONG_MAX / 10)
				|| (nb == LONG_MAX / 10 && str[i] >= '7')))
			return (-1);
		else if (sign == -1 && ((nb > LONG_MIN / 10 * -1)
				|| (nb == LONG_MIN / 10 * -1 && str[i] >= '8')))
			return (0);
		nb = nb * 10 + str[i++] - '0';
	}
	return (sign * (int)nb);
}

static int	ft_sign_check(const char *str)
{
	if (*str == '+')
		return (1);
	else
		return (-1);
}
// char	*search_from_envp(char *word)
// {
// 	int	i;
// 	char	*path;
// 	char	**ret_split;

// 	i = 0;
// 	path = NULL;
// 	while (check[i])
// 	{
// 		if (ft_strncmp(check[i], word, ft_strlen(word)) == 0) // 찾으면 0
// 		{
// 			ret_split = ft_split(check[i], '=');
// 			path = ft_strdup(ret_split[1]);
// 			free_2d(ret_split);
// 			break ;
// 		}
// 		++i;
// 	}
// 	return (path);
// }

void	free_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_cnt;

	if (s == NULL)
		return (NULL);
	word_cnt = ft_word_count(s, c);
	array = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (array == NULL)
		system_call_error(ALLOC_FAIL);
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

int	ft_stat(char *path, t_node *cmd)
{
	struct stat statbuf;

	if (stat(path, &statbuf) == -1)
		cmd_not_found_error(cmd);
	return (0);
}

void	ft_exit(int error)
{
	set_or_get_status(error);
	exit(error);
}

int	set_or_get_status(int error) // -1 get status, >= 0 set status
{
	static int status;

	if (error >= 0)
		status = error;
	return (status);
}

void	cmd_not_found_error(t_node *cmd)
{
	char	*err_str;

	err_str = "❀ ❂ smash 🍾 ";
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	err_str = cmd->content;
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	err_str = " 🍾 hey~ command not found\n";
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	ft_exit(CMD_NOT_FOUND);
}

void	system_call_error(int error)
{
	char	*err_str;

	err_str = strerror(error);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
	if (error == ALLOC_FAIL)
		ft_exit(ALLOC_FAIL);
	else if (error == EACCES || error == ENOEXEC)
		ft_exit(EXEC_FILE_FAIL);
	else
		ft_exit(GENERAL_ERROR);
}

void	builtin_error(void)
{
	char	*err_str;

	err_str = strerror(errno);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
	set_or_get_status(GENERAL_ERROR);
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
	if (flag == SUCCESS)
		printf("!ALERT! 정상 종료!\n");
	exit (flag);
}
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
		system_call_error(ALLOC_FAIL);
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
		system_call_error(ALLOC_FAIL);
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
