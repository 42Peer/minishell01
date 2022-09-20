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
		system_call_error();
	ft_memcpy(copy, str + info->start_idx, len);
	token = ft_lstnew(info->token_type, copy);
	ft_lstadd_back(&(info->token_list), token);
	info->token_type = NONE;
	return (0);
}

t_token	*tokenize(char *str)
{
	t_token_info	info;

	info.start_idx = 0;
	info.cur_idx = 0;
	info.sin_quoted = 0;
	info.dou_quoted = 0;
	info.token_type = NONE;
	info.token_list = NULL;

	while (str[info.cur_idx])
	{
		if ((!info.sin_quoted && !info.dou_quoted) && ((info.token_type == T_REDIR || info.token_type == T_PIPE)))
		{ // 2~3 인용중이지 않고, 이전 문자가 연산자의 일부
			if (is_operator(str[info.cur_idx]))
			{
				make_token(str, info.cur_idx, &info); // <- add_list_token();
			}
			else
			{
				make_token(str, info.cur_idx - 1, &info);
				if (!is_whitespace(str[info.cur_idx]))
				{
					info.start_idx = info.cur_idx;
					info.token_type = T_WORD;
				}
			}
		}
		else if ((!info.sin_quoted && !info.dou_quoted) && is_quote(str[info.cur_idx]))
		{  // 4 인용중이지 않고, 인용시작
			if (str[info.cur_idx] == '\'')
				info.sin_quoted = 1;
			else if (str[info.cur_idx] == '"')
				info.dou_quoted = 1;
			if (info.token_type == NONE)
			{
				info.start_idx = info.cur_idx;
				info.token_type = T_WORD;
			}
		}
		else if ((!info.sin_quoted && !info.dou_quoted) && is_operator(str[info.cur_idx]))
		{ // 6 인용중이지 않고, 현재 인덱스가 연산자
			if (info.token_type != NONE)
				make_token(str, info.cur_idx - 1, &info);
			info.start_idx = info.cur_idx;
			if (str[info.cur_idx] == '|')
				info.token_type = T_PIPE;
			else
				info.token_type = T_REDIR;
		}
		else if ((!info.sin_quoted && !info.dou_quoted) && is_whitespace(str[info.cur_idx]))
		{ // 8 인용중이지 않고, 현재 인덱스가 blank
			if (info.token_type != NONE)
				make_token(str, info.cur_idx - 1, &info);
		}
		else if (info.token_type == T_WORD)
		{ // 9 이전 문자가 단어의 한 부분일 때
			if (info.sin_quoted && str[info.cur_idx] == '\'')
				info.sin_quoted = 0;
			else if (info.dou_quoted && str[info.cur_idx] == '"')
				info.dou_quoted = 0;
		}
		else
		{ // 11 현재 문자가 새로운 단어의 시작
			info.start_idx = info.cur_idx;
			info.token_type = T_WORD;
		}
		++info.cur_idx;
	}
	if (info.sin_quoted || info.dou_quoted)
	{
		printf("WARNING: syntax error! non-quoted!\n");
		cleaner(NULL, NULL, info.token_list);
		return (NULL);
	}
	if (info.token_type != NONE) // 1 eof or NULL을 만나면 
		make_token(str, info.cur_idx - 1, &info);
	return (info.token_list);
}

// make_token에서 token_type == NONE일 때 아무것도 저장하지 않게 처리.
// make_token 내부에서 token_type을 NONE으로 초기화.