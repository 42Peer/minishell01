#include "minishell.h"

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);



char	*save(char *src, char c, size_t len)	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
{//c는 다음글자
//	char test[2];
//	test[0] = c;
//	test[1] = '\0';
	if (!src)
		return (ft_strdup(""));
//	size_t len = ft_strlen(src);
	char *dst = malloc(sizeof(char) * (len + 2));

	ft_strlcpy(dst, src, len + 1);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(src);
	return (dst);
}

char	*dollar_sign(char *str, int *i)
{
	;
}

char    *single_quote(char *str, int *i)	// '를 만났을 때, ' 다음 인덱스(i)부터 들어옴
{
    char    *piece;
    int     douq_idx = 0;
    int     start = *i + 1;
	int		dollar_idx = 0;

	piece = ft_strdup("");
    while (str[*i + 1])		// ' 다음 인덱스부터 토큰 끝까지 읽기
    {
		if (str[*i + 1] == '$')
			dollar_idx = *i + 1;
		if (!douq_idx && str[*i + 1] == '"')	// 처음 "를 만났을 때 위치 저장해두기
			douq_idx = *i + 1;
		if (str[*i + 1] == '\'')	// '가 닫히는 부분
		{
//			if (start == *i + 1)
//				piece = ft_strdup("");
			while (start <= *i)
				piece = save(piece, str[start++], ft_strlen(piece));	// 인용 제거 한 부분 저장
			*i += 1;
			return (piece);		// 인용 제거한 부분 리턴
		}
		*i += 1;
    }		// '가 안 닫혔을 때 빠져나옴
	if (dollar_idx > douq_idx && douq_idx)	// "가 저장되어 있을 때
    {
		while (start - 1 <= douq_idx - 1)	// ' 포함하고 ~ " 전까지
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
        *i = douq_idx - 1;	// 커서 위치 "로
	}
	else			// "도 없을 때
	{
		if (dollar_idx)
			*i = dollar_idx - 1;
		while (start - 1 <= *i)	// ' 포함하고 ~ \0 전 까지
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
//		*i += 1; 	// 커서 위치 \0로
	}
    return (piece);
}

char	*double_quote(char *str, int *i)
{
	char    *piece;
	int     sigq_idx = 0;
	int     start = *i + 1;
	int		dollar_idx = 0;


	piece = ft_strdup("");
    while (str[*i + 1])
    {
		if (!sigq_idx && str[*i + 1] == '\'')
			sigq_idx = *i + 1;
		else if (str[*i + 1] == '$')
			dollar_idx = *i + 1;
		else if (str[*i + 1] == '"')
		{
//			if (start == *i + 1)
//				piece = ft_strdup("");
			while (start <= *i)
			{
				if (str[start] == '$')		// 환경변수 확장
				{	
					piece = save(piece, '0', ft_strlen(piece));
					start++;
				}
				else
					piece = save(piece, str[start++], ft_strlen(piece));
			}
			*i += 1;
			return (piece);
		}
		*i += 1;
	}
	if (dollar_idx > sigq_idx && sigq_idx)
    {
		while (start - 1 <= sigq_idx - 1)
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
    	*i = sigq_idx - 1;
	}
	else
	{
		if (dollar_idx)
			*i = dollar_idx - 1;
		while (start - 1 <= *i)
		{
//			if (str[start] == '$')		// 환경변수 확장
//				piece = save(piece, '0', ft_strlen(piece));
//			else
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
//			piece = save(piece, str[start++ - 1], ft_strlen(piece));
		}
//		*i += 1;
	}
	return (piece);
}

char	*delquote(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			ptr = ft_strjoin(ptr, single_quote(str, &i));
		else if (str[i] == '"')
			ptr = ft_strjoin(ptr, double_quote(str, &i));
		else if (str[i] == '$') //  && type != here_doc
			ptr = save(ptr, '0', ft_strlen(ptr));
//			ptr = ft_strjoin(ptr, dollar_sign(str, &i))확장;
		else
			ptr = save(ptr, str[i], ft_strlen(ptr));
		++i;
	}
//	free(str);
	return (ptr);
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
	if (token_info.token_type != NONE) // 1 eof or NULL을 만나면 
		make_token(str, token_info.cur_idx - 1, &token_info);
	return (token_info.token_list);
}

// make_token에서 token_type == NONE일 때 아무것도 저장하지 않게 처리.
// make_token 내부에서 token_type을 NONE으로 초기화.