
정리 정돈 함수
{
	if (토큰 타입 == T_WORD)
		인용 제거(토큰 노드);
		확장(토큰 노드);
	else if (토큰 타입 == T_REDIR)
}

인용 제거 함수(토큰 노드)
{
	변수 ' 무시 플래그, " 무시 플래그, ' 카운트, " 카운트, 글자 카운트, 확장 플래그;

	while (컨텐츠 한번 읽기) <- 첫번째 돌면서
	{
		' ", 그 외 글자들 카운팅;
		if (' "가 짝수가 아니면)
			'나 " 무시 플래그 켜기
			그 외 글자들 += ' " 글자수;
	}//글자수 확인
	char *no_quote = calloc(카운트, sizeof(char));
	while (컨텐츠 한번 읽기) <- 두번째 돌면서
	{
		if (무시 플래그 확인 && ' "가 아니면)
			no_quote에 한글자 넣기;
		++인덱스;
	}
	free (기존 컨텐츠);
	컨텐츠 = no_quote;
}

char	*확장(토큰 노드)
{
	while (content를 돌면서)
		if ($를 만나면) {
			++현재 인덱스;	-> $ 바로 다음 글자 가리키게
			시작 인덱스 = 현재 인덱스;
			while (문자열 끝까지)
			{
				if (영문자, 숫자, _가 아니면)
					break ;
				++현재 인덱스;
			}
			검색어 = 시작 인덱스부터 현재 인덱스 - 1까지
			환경 변수 찾는 함수(검색어);	<- 여기서 리턴함
		}
		++현재 인덱스;
}

환경 변수 찾는 함수(검색어)
{
	while (환경 변수를 돌면서)
		tmp = split(환경 변수, '=');
		if (tmp[0] == 검색어)
		{
			tmp[1]만 복사하고
			free(tmp);
			return (복사값);
		}
		free(tmp);
	return (NULL);
}

#	인용 -> 히어독 -> 확장 -> 리디렉션 -> 파이프
부모 처리 함수
{
	
}

char	*translate(char *str)
{
	while (str[i])
	{
		if (str[i] == '"' && duoq == 2)
			환경변수찾기()
	}
}

char	*save(char *src, char c, int len)	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
{//c는 다음글자
	if (!src)
		return (ft_strdup(&c));
	char *dst = malloc(sizoef(char) * (len + 2));
	ft_strlcpy(dst, src, len);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(src);
	return (dst);
}


char    *single_quote(char *str, int *i)	// '를 만났을 때, ' 다음 인덱스(i)부터 들어옴
{
    char    *piece;
    int     douq_idx = 0;
    int     start = *i + 1;
	int		dollar_idx = 0;

	piece = NULL;
    while (str[*i + 1])		// ' 다음 인덱스부터 토큰 끝까지 읽기
    {
		if (str[*i + 1] == '$')
			dollar_idx = *i + 1;
		if (!douq_idx && str[*i + 1] == '"')	// 처음 "를 만났을 때 위치 저장해두기
			douq_idx = *i + 1;
		if (str[*i + 1] == '\'')	// '가 닫히는 부분
		{
			while (start <= *i)
					piece = save(piece, str[start++], ft_strlen(piece));	// 인용 제거 한 부분 저장
			*i += 2;
			return (piece);		// 인용 제거한 부분 리턴
		}
	}
	*i += 1;
    }		// '가 안 닫혔을 때 빠져나옴
	if (duoq_idx)	// "가 저장되어 있을 때
      	while (start - 1 <= douq_idx - 1)	// ' 포함하고 ~ " 전까지
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
        *i = douq_idx;	// 커서 위치 "로
    else			// "도 없을 때
	{
		if (dollar_idx)
			*i = dollar_idx - 1;
		while (start - 1 <= *i)	// ' 포함하고 ~ \0 전 까지
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
		*i += 1; 	// 커서 위치 \0로
	}
    return (piece);
}

char	*double_quote(char *str, int *i)
{
	char    *piece;
	int     sigq_idx = 0;
	int     start = *i + 1;

	piece = NULL;
    while (str[*i + 1])
    {
		if (!sigq_idx && str[*i + 1] == '\'')
			sigq_idx = *i + 1;
		else if (!sign_idx && str[*i + 1] == '$')
			확장 해주기;
		else if (str[*i + 1] == '"')
		{
			while (start <= *i)
			{
				if (str[start] == '$')		// 환경변수 확장
					piece = strjoin(piece, 확장해주는 함수(piece, start);
				else
					piece = save(piece, str[start++], ft_strlen(piece));
			}
			return (piece);
		}
	}
	*i += 1;
	}
	if (sigq_idx)
       	while (start - 1 <= sigq_idx - 1)
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
        *i = douq_idx;
    else
		while (start - 1 <= *i)
			piece = save(piece, str[start++ - 1], ft_strlen(piece));
		*i += 1;
    return (piece);
}

char	*delquote(char *str, int type)
{
	char	*ptr;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ptr = ft_strjoin(ptr, single_quote(str, &i));
		else if (str[i] == '"')
			ptr = ft_strjoin(ptr, double_quote(str, &i));
		else if (str[i] == '$' && type != here_doc)
			확장;
		else
			ptr = save(ptr, str[i], ft_strlen(ptr));
		++i;
	}
	free(str);
	return (ptr);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			sigq++;
			if (sigq == 1)
				end = i - 1;
				ptr = ft_substr(str, start, end + 1);

			if (sigq == 2 && !expansion)
				start = i + 1;
				expansion = 1;
				expansion_str = translate(str + i);
			i++;
		}
		if (str[i] == '"')
		{
			douq++;
			if (douq == 2 && !expansion)
				expansion = 1;
				expansion_str = 
			i++;
		}
		else
		{
			i++;
		}
		if (expansion)
			sigq = 0;
			douq = 0;
			dexpansion = 0;
			ptr = ft_strjoin(ptr, str);
	}
	ptr = ft_calloc((count + 1) * sizeof(char));
	return (ptr);
}

char	*인용, 확장(t_node *node)
{
	char *ptr = node->content;
	char *return;

	while (*ptr)
	{
		ptr = ft_strtrim()
		return = ft_join(ptr, return);
		if (*ptr == '\0')
			break;
	}
	return (return);
}

#
#
#				교리님 인용제거 함수  
#
#
#

typedef enum e_quote
{
	UNQUOTED = 0,
	QUOTED
} t_quoted_state;

typedef enum e_expand
{
	UNEXPANDED = 0,
	EXPANDED
} t_expand_state;

typedef struct s_quoted
{
	t_quoted_state	double_quoted;
	t_quoted_state	single_quoted;
	t_expand_state	*arry_expand_state;
	char			*quoted_str;
} t_quote;

static int	is_remove_double_quote(char *str, t_quote *pq)
{
	if (pq->single_quoted == QUOTED)
		return (0);
	if (pq->double_quoted == UNQUOTED)
	{
		if (ft_strchr(str + 1, '\"'))
		{
			pq->double_quoted = QUOTED;
			return (1);
		}
		return (0);
	}
	pq->double_quoted = UNQUOTED;
	return (1);
}

static int	is_remove_single_quote(char *str, t_quote *pq)
{
	if (pq->double_quoted == QUOTED)
		return (0);
	if (pq->single_quoted == UNQUOTED)
	{
		if (ft_strchr(str + 1,'\''))
		{
			pq->single_quoted = QUOTED;
			return (1);
		}
		return (0);
	}
	pq->single_quoted = UNQUOTED;
	return (1);
}

static int	is_need_to_expand_value(t_quote *pq)
{
	return (!pq->single_quoted);
}

static int	str_to_quoted_str(char *str, t_quote *pq)
{
	int		idx;
	int		quoted_idx;
	int		expand_idx;

	if ((str == 0) || (pq == 0))
		return (-1);
	idx = 0;
	quoted_idx = 0;
	expand_idx = 0;
	while (str[idx])
	{
		if (str[idx] == '"')
		{
			if (!is_remove_double_quote(str + idx, pq))
				pq->quoted_str[quoted_idx++] = str[idx];
		}
		else if (str[idx] == '$')
		{
			if (is_need_to_expand_value(pq))
				set_expanded(pq, expand_idx++);
			pq->quoted_str[quoted_idx++] = '$';
		}
		else if (str[idx] == '\'')
		{
			if (!is_remove_single_quote(str + idx, pq))
				pq->quoted_str[quoted_idx++] = str[idx];
		}
		else
			pq->quoted_str[quoted_idx++] = str[idx];
		idx++;
	}
	return (0);
}

int	make_quoted_str(char *str, t_quote *pq)
{
	size_t	len;

	if ((str == 0)  || (pq == 0))
		return (-1);
	len = ft_strlen(str);
	pq->quoted_str = ft_calloc(len + 1, sizeof(char));
	if (pq->quoted_str == 0)
		return (-1);
	if (calloc_expand_arry(str, pq) < 0)
		return (-1);
	if (str_to_quoted_str(str, pq) < 0)
		return (-1);
	return (0);
}