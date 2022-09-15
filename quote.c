#include "minishell.h"

char	*save(char *src, char c, size_t len)	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
{
	char	*dst;

	if (!src)
		src = ft_strdup("");
	dst = malloc(sizeof(char) * (len + 2));
	ft_strlcpy(dst, src, len + 1);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(src);
	src = NULL;
	return (dst);
}

int	is_expandable(char *str, int i)
{
	if (('A' <= str[i] && str[i] <= 'Z')
		|| ('a' <= str[i] && str[i] <= 'z')
		|| ('0' <= str[i] && str[i] <= '9')
		|| (str[i] == '_'))
		return (1);
	else
		return (0);
}

char	*dollar_sign(char *str, int *env_i)		// i는 $ 인덱스
{
	char	*value;
	char	*env_key;
	int		i;
	int		len;
	// $USER-
	// 012345
	// ^  처음엔 여기 가리키는중
	//  ^ 여기부터 가리켜야함.

	/* (1)영문자, 숫자, _가 아닌 부분까지 읽고 */
	i = *env_i + 1;
	while (is_expandable(str, i))	// while을 빠져나오면 i는 환경변수명 조건이 아닌 위치
		++i;
	/* (2)env_key = 해당 부분까지 넣기; */
	len = i - *env_i - 1;
	env_key = ft_substr(str, (unsigned int)((*env_i) + 1), len);
	*env_i = i - 1; 			// i = 환경변수명 가장 마지막 글자 인덱스로 업데이트
	value = getenv(env_key);
	if (env_key)
		free(env_key);
	if (!value)
		return (ft_strdup(""));
	else
		return (ft_strdup(value));
}

//    sumsong ~ing    수정 필요!
char	*reset_cursor(char *str, int quote_i, int env_i, int *origin_i)
{
	char	*piece;
	int		i;

	piece = ft_strdup("");
	if ((quote_i && env_i && quote_i < env_i) || (quote_i && !env_i))						// "만 있을 때
		i = quote_i;
	else if ((quote_i && env_i && quote_i > env_i) || (!quote_i && env_i))						// $만 있을 때
		i = env_i;
	while (*origin_i < i)
		piece = save(piece, str[(*origin_i)++], ft_strlen(piece));
	--(*origin_i);
	return (piece);
}

char	*single_quote(char *str, int *quote_i, int *quoted)	// '를 만났을 때, ' 인덱스(i)부터 들어옴
{
	char	*piece;
	int		env_i;
	int		douq_i;
	int		i;
	
	i = *quote_i;	// 커서 i를 ' 다음 인덱스로
	env_i = 0;
	douq_i = 0;
	piece = ft_strdup("");
	while (str[++i])		// ' 다음 인덱스부터 ~ 토큰 끝(\0)까지
	{
		if (!env_i && str[i] == '$')	// 처음 $ 만나서 위치 저장
			env_i = i;
		if (!douq_i && str[i] == '"')	// 처음 "를 만났을 때 위치 저장해두기
			douq_i = i;
		if (str[i] == '\'')	// '가 닫히는 부분
		{
			if (!quoted)
				*quoted = 1;
			while (++(*quote_i) < i)	// ' 시작 점부터 현재 위치까지
				piece = save(piece, str[*quote_i], ft_strlen(piece));	// 인용 제거 한 부분 저장
			return (piece);		// 인용 제거한 부분 리턴
		}
	}					// '가 안 닫혔을 때 빠져나옴
	// piece = reset_cursor(str, douq_i, env_i, quote_i);
	if ((douq_i && env_i && douq_i < env_i) || (douq_i && !env_i))						// "만 있을 때
		i = douq_i;
	else if ((douq_i && env_i && douq_i > env_i) || (!douq_i && env_i))						// $만 있을 때
		i = env_i;
	while (*quote_i < i)
		piece = save(piece, str[(*quote_i)++], ft_strlen(piece));
	--(*quote_i);
	return (piece);
}

char	*double_quote(char *str, int *quote_i, int *quoted)		// quote_i는 " 위치.
{
	char	*piece;
	int		env_i;
	int		sigq_i;
	int		i;
	
	i = *quote_i;	// " 다음 인덱스
	env_i = 0;
	sigq_i = 0;
	piece = ft_strdup("");
	while (str[++i])
	{
		if (!sigq_i && str[i] == '\'')
			sigq_i = i;
		else if (!env_i && str[i] == '$')
			env_i = i;
		else if (str[i] == '"')		// "로 닫혔을 때
		{
			if (!quoted)
				*quoted = 1;
			while (++(*quote_i) < i)
			{
				if (str[(*quote_i)] == '$')		// 환경변수 확장
					piece = ft_strjoin(piece, dollar_sign(str, quote_i));
				else
					piece = save(piece, str[*quote_i], ft_strlen(piece));
			}
			return (piece);
		}
	}
	// piece = reset_cursor(str, sigq_i, env_i, quote_i);
	if ((sigq_i && env_i && sigq_i < env_i) || (sigq_i && !env_i))
		i = sigq_i;
	else if ((sigq_i && env_i && sigq_i > env_i) || (!sigq_i && env_i))
		i = env_i;
	while (*quote_i < i)
		piece = save(piece, str[(*quote_i)++], ft_strlen(piece));
	--(*quote_i);
	return (piece);
}

char	*delquote(char *str, int *quoted)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = ft_strdup("");
	while (str && str[i])
	{
		if (str[i] == '\'')
			ptr = ft_strjoin(ptr, single_quote(str, &i, quoted));
		else if (str[i] == '"')
			ptr = ft_strjoin(ptr, double_quote(str, &i, quoted));
		else if (str[i] == '$' && *quoted != 1) //  && type != here_doc
			ptr = ft_strjoin(ptr, dollar_sign(str, &i));
		else
			ptr = save(ptr, str[i], ft_strlen(ptr));
		++i;
	}
//	free(str);
	return (ptr);
}
