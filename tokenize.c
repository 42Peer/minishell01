#include "minishell.h"

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

int	make_token(char *str, int copy_idx, t_token_info *info)
{
	char	*copy;
	size_t	len;
	t_token	*token;

	if ((str == NULL) || (info == NULL))
		return (ERROR);
	len = copy_idx - info->start_idx + 1;
	copy = ft_calloc(len + 1, sizeof(char));
	if (!copy)
		clean_exit(ERROR, copy, info->token_list, NULL);
	ft_memcpy(copy, str + info->start_idx, len);
	token = ft_lstnew(info->token_type, copy);
	if (!token)
		clean_exit(ERROR, copy, info->token_list, NULL);
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
		if (!token_info.quoted_flag && ((token_info.token_type == T_REDIR || token_info.token_type == T_PIPE)))
		{ // 2~3 인용중이지 않고, 이전 문자가 연산자의 일부
			if (is_operator(str[token_info.cur_idx]))
			{
				make_token(str, token_info.cur_idx, &token_info); // <- add_list_token();
			}
			else
			{
				make_token(str, token_info.cur_idx - 1, &token_info);
				if (!is_whitespace(str[token_info.cur_idx]))
				{
					token_info.start_idx = token_info.cur_idx;
					token_info.token_type = T_WORD;
				}
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
			if (token_info.token_type != NONE)
				make_token(str, token_info.cur_idx - 1, &token_info);
			token_info.start_idx = token_info.cur_idx;
			if (str[token_info.cur_idx] == '|')
				token_info.token_type = T_PIPE;
			else
				token_info.token_type = T_REDIR;
		}
		else if (!token_info.quoted_flag && is_whitespace(str[token_info.cur_idx]))
		{ // 8 인용중이지 않고, 현재 인덱스가 blank
			if (token_info.token_type != NONE)
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
	if (token_info.quoted_flag)
		printf("WARNING: syntax error! non-quoted!\n");
	if (token_info.token_type != NONE) // 1 eof or NULL을 만나면 
		make_token(str, token_info.cur_idx - 1, &token_info);
	return (token_info.token_list);
}

// make_token에서 token_type == NONE일 때 아무것도 저장하지 않게 처리.
// make_token 내부에서 token_type을 NONE으로 초기화.