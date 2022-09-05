#include "minishell.h"

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
		return (0);
	ft_bzero(ary, count * size);
	return (ary);
}

t_token	*ft_lstnew(int type, char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
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




int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

void	get_error(int error, char *tmp, t_token_info *info)		// free도 추가
{
	if (tmp)
		free(tmp);
	if (info->token_list)
		ft_lstclear(&(info->token_list));
	if (error == ERROR)
		exit (ERROR);
}

int	make_token(char *str, int copy_idx, t_token_info *info)
{
	char	*tmp;
	size_t	len;
	t_token	*token;
	
	if ((str == NULL) || (info == NULL))
		return (ERROR);
	len = copy_idx - info->start_idx + 1;
	tmp = ft_calloc(len + 1, sizeof(char));
	if (tmp == 0)
		get_error(ERROR, NULL, info);
	ft_memcpy(tmp, str + info->start_idx, len);
	token = ft_lstnew(token->type, tmp);
	if (!token)
		get_error(ERROR, NULL, info);
	ft_lstadd_back(&(info->token_list), token);
	info->token_type = NONE;
	return (0);
}

t_token	*tokenize(char *str)
{
	t_token_info	token_info;

	token_info.start_idx = 0;
	token_info.cur_idx = 0;
	token_info.quoted_flag = 0;
	token_info.token_type = NONE;
	token_info.token_list = NULL;
	while (str[token_info.cur_idx])
	{
		if (!token_info.quoted_flag && ((token_info.token_type == T_REDIR) || (token_info.token_type == T_PIPE)))
		{ // 2~3 인용중이지 않고, 이전 문자가 연산자의 일부
			if (is_operator(str[token_info.cur_idx]))
			{
				make_token(str, token_info.cur_idx, &token_info); // <- add_list_token();
			}
			else
			{
				make_token(str, token_info.cur_idx - 1, &token_info);
			}
		}
		else if (!token_info.quoted_flag && is_quote(str[token_info.cur_idx])) 
		{  // 4 인용중이지 않고, 인용시작
			token_info.quoted_flag = 1;
			if (token_info.token_type == NONE)
			{
				token_info.start_idx = token_info.cur_idx;
				token_info.token_type = T_WORD;
			}
		}
		else if (!token_info.quoted_flag && is_operator(str[token_info.cur_idx]))
		{ // 6 인용중이지 않고, 현재 인덱스가 연산자
			make_token(str, token_info.cur_idx - 1, &token_info);
			token_info.start_idx = token_info.cur_idx;
			if (str[token_info.cur_idx] == '|')
				token_info.token_type = T_PIPE;
			else
				token_info.token_type = T_REDIR;
		}
		else if (!token_info.quoted_flag && is_whitespace(str[token_info.cur_idx]))
		{ // 8 인용중이지 않고, 현재 인덱스가 blank
			make_token(str, token_info.cur_idx - 1, &token_info);
		}
		else if (token_info.token_type == T_WORD)
		{ // 9 이전 문자가 단어의 한 부분일 때
			if (token_info.quoted_flag && is_quote(str[token_info.cur_idx]))
				token_info.quoted_flag = 0;
		}
		else
		{ // 11 현재 문자가 새로운 단어의 시작
			token_info.start_idx = token_info.cur_idx;
			token_info.token_type = T_WORD;
		}
		++token_info.cur_idx;
	}
	if (token_info.token_type != NONE) // 1 eof or NULL을 만나면 
		make_token(str, token_info.cur_idx - 1, &token_info);
	return (token_info.token_list);
}

int main(int argc, char **argv, char **envp)
{
	char	*str;
	// t_process *root;
	t_token	*head_token;

	while (1)
	{
		str = readline("minishell > "); // 1. 입력 받기
		if (strcmp(str, "exit") == 0) // || (ctrl-d signal)) // 종료 조건
			break;
//		else if (SIGINT :ctrl-C signal)
//			printf("\n");
//		else if (ctrl-\ sig)
//			;
		else
		{
			printf("input : %s\n", str);
			head_token = tokenize(str); // 2. 토큰화
			ft_lstiter(head_token, print_content);
//			int i = -1;
//			while (++i < ft_lstsize(head_token))
//				ft_lstiter(head_token, (*printf)("%s\n", head_token->content));
		}
		// root = make_tree(head_token); // 토큰을 자료구조에 넣는다
		add_history(str);
		free(str);
		str = NULL;
	}
	return(0);
}


// make_token에서 token_type == NONE일 때 아무것도 저장하지 않게 처리.
// make_token 내부에서 token_type을 NONE으로 초기화.