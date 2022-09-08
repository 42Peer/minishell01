
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

char	*save(char *src, char c, int len)
{//c는 다음글자
	if (!src)
		return (0);
	char *dst = malloc(sizoef(char) * (len + 2));
	ft_strlcpy(dst, src, len);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(src);
	return (dst);
}

char	*sigq(char *str, int *i)
{
	char	*ptr;
	int sigq = 1;
	int	duoq = 0;
	int	start = *i + 1;

	while (str[*i + 1] && !duoq)
	{
		if (str[*i + 1] == '"')
			duoq++;
		if (str[*i + 1] == '\'')
		{
			while (start <= *i)
				ptr = save(ptr, str[start], ft_strlen);
			*i += 1;
			return (ptr);
		}
		*i += 1;
	}
	return (NULL);
}

char	*duoq(char *str, int *i)
{
	int duoq = 1;
}

char	*delquote(char *str)
{
	char *ptr;
	char *expansion_str;
	int len = ft_strlen();
	int	sigq = 0;
	int	douq = 0;
	int	expansion = 0;
	int start = 0;
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '\'')
			ptr = ft_strjoin(ptr, sigq(str, &i));
		if (str[i] == '"')
			ptr = duoq(str + i, &i);
		ptr = save(ptr, str[i], ft_strlen(ptr));
	}

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
