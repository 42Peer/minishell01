#include "minishell.h"

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);


char	*save(char *src, char c, size_t len)	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
{
//	char test[2];
//	test[0] = c;
//	test[1] = '\0';
	if (!src)
		src = ft_strdup("");
//	size_t len = ft_strlen(src);
	char *dst = malloc(sizeof(char) * (len + 2));

	ft_strlcpy(dst, src, len + 1);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(src);
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
	*env_i = i - 1; 		// i = 환경변수명 가장 마지막 글자 인덱스로 업데이트
	value = ft_strdup(getenv(env_key));
	if (!value)
		value = ft_strdup("");
	if (env_key)
		free(env_key);
	return (value);
}

char    *single_quote(char *str, int *quote_i)	// '를 만났을 때, ' 인덱스(i)부터 들어옴
{
    char    *piece;
	int		env_i = 0;
    int     douq_i = 0;
    int     i = *quote_i;	// 커서 i를 ' 다음 인덱스로

	piece = ft_strdup("");
	while (str[++i])		// ' 다음 인덱스부터 ~ 토큰 끝(\0)까지
	{
		if (!env_i && str[i] == '$')	// 처음 $ 만나서 위치 저장
			env_i = i;
		if (!douq_i && str[i] == '"')	// 처음 "를 만났을 때 위치 저장해두기
			douq_i = i;
		if (str[i] == '\'')	// '가 닫히는 부분
		{
			while (++(*quote_i) < i)	// ' 시작 점부터 현재 위치까지
				piece = save(piece, str[*quote_i], ft_strlen(piece));	// 인용 제거 한 부분 저장
			return (piece);		// 인용 제거한 부분 리턴
		}
	}					// '가 안 닫혔을 때 빠져나옴
	if ((douq_i && env_i && douq_i < env_i)			// "가 $보다 먼저 오거나
		|| (douq_i && !env_i))						// "만 있을 때
		i = douq_i;
	else if ((douq_i && env_i && douq_i > env_i)	// $가 "보다 먼저 오거나
		|| (!douq_i && env_i))						// $만 있을 때
		i = env_i;
	while (*quote_i < i)
		piece = save(piece, str[(*quote_i)++], ft_strlen(piece));
	--(*quote_i);
	return (piece);
}

char	*double_quote(char *str, int *quote_i)		// quote_i는 " 위치.
{
	char    *piece;
	int		env_i = 0;
	int     sigq_i = 0;
	int		i = *quote_i;	// " 다음 인덱스
//	int     start = *i + 1;

	piece = ft_strdup("");
    while (str[++i])
    {
		if (!sigq_i && str[i] == '\'')
			sigq_i = i;
		else if (!env_i && str[i] == '$')
			env_i = i;
		else if (str[i] == '"')		// "로 닫혔을 때
		{
			while (++(*quote_i) < i)
			{
				if (str[(*quote_i)] == '$')		// 환경변수 확장
				{
					// piece = save(piece, '0', ft_strlen(piece));	// 확장 위치 확인용
					piece = ft_strjoin(piece, dollar_sign(str, quote_i));
				}
				else
					piece = save(piece, str[*quote_i], ft_strlen(piece));
			}
			return (piece);
		}
	}
	if ((sigq_i && env_i && sigq_i < env_i)			// '가 $보다 먼저 오거나
		|| (sigq_i && !env_i))						// '만 있을 때
		i = sigq_i;
	else if ((sigq_i && env_i && sigq_i > env_i)	// $가 '보다 먼저 오거나
		|| (!sigq_i && env_i))						// $만 있을 때
		i = env_i;
	while (*quote_i < i)
	{
		piece = save(piece, str[(*quote_i)++], ft_strlen(piece));
		// ++*quote_i;
	}
	--(*quote_i);
	return (piece);
}

char	*delquote(char *str)
{
	char	*ptr;
	int		i;
	char	*tmp = NULL;

	i = 0;
	ptr = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
		{
			tmp = single_quote(str, &i);
			ptr = ft_strjoin(ptr, tmp);
		}
		else if (str[i] == '"')
		{
			tmp = double_quote(str, &i);
			ptr = ft_strjoin(ptr, tmp);
		}
		else if (str[i] == '$') //  && type != here_doc
		{	// ptr = save(ptr, '0', ft_strlen(ptr));
			tmp = dollar_sign(str, &i);
			ptr = ft_strjoin(ptr, tmp);
		}
		else
			ptr = save(ptr, str[i], ft_strlen(ptr));
		if (tmp)
			free(tmp);
		++i;
	}
	if (str)
		free(str);
	return (ptr);
}
