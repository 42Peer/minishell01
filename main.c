#include "minishell.h"
/*
root
 |
process(pipe)
 |                              \
[       phrase       ]       process(pipe)
 |              |
redirection    cmd
*/

// << hi echo hi > file3 a b c >file2 | wc -l
// 하나의 프로세스 노드에서
// 현재토큰에서
// RIDERIECTION 노드 만들기();

char	*delquote(char *str);
char	*save(char *src, char c, int len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이



size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}


char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] && dst_len + i + 1 < dstsize)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * len_s1 + len_s2 + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcat(ptr, s2, len_s1 + len_s2 + 1);
	return (ptr);
}

int main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;

	ds.head_token = NULL;
	ds.root_node = NULL;
//	char ccc = 'd';
//	printf("%s\n", save(str, ccc, ft_strlen(&ccc)));
	while (1)
	{
		str = readline("minishell > "); // 1. 입력 받기
		if (strcmp(str, "exit") == 0) // || (ctrl-d signal)) // 종료 조건
			break;
		printf("%s\n", delquote(str));
//		else if (SIGINT :ctrl-C signal)
//			printf("\n");
//		else if (ctrl-\ sig)
//			;
		/*
		else
		{
			printf("input : %s\n", str);
			ds.head_token = tokenize(str); // 2. 토큰화
			ft_lstiter(ds.head_token, print_content);
//			int i = -1;
//			while (++i < ft_lstsize(head_token))
//				ft_lstiter(head_token, (*printf)("%s\n", head_token->content));
		}
		make_tree(&ds); // 토큰을 자료구조에 넣는다
		ft_traverse(ds.root_node);
		add_history(str);
		free(str);
		*/
	}
	//clean_exit(SUCCESS, NULL, NULL, &ds);
	return (0);
}
