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

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0 || !s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i + 1 < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(char *s1)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!copy)
		system_call_error(ALLOC_FAIL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
//	free(s1);
	return (copy);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
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

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
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
char	*ft_strjoin_no_free(char *s1, char *s2)
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
	{
		set_or_get_status(errno);
		return (NULL);
	}
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcat(ptr, s2, len_s1 + len_s2 + 1);
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
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
		system_call_error(ALLOC_FAIL);
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcat(ptr, s2, len_s1 + len_s2 + 1);
	free(s1);
	free(s2);
	return (ptr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		system_call_error(ALLOC_FAIL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		++i;
	}
	substr[i] = '\0';
	return (substr);
}


int main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;
	int			flag;

	flag = 0;
	check = envp;
	ds.head_token = NULL;
	ds.root_node = NULL;
	if (argc)
		(void)argv;
	make_env_list(envp, &ds);
	make_env_array(envp, &ds);
	// int i = 0;
	// while ((ds.env_array)[i])
		// printf("%s\n", ds.env_array[i++]);
	// env_lstiter(ds.head_env, print_content);	// 출력용 함수
	// signal_handler();
	while (1)
	{
		str = readline("minishell > "); // 1. 입력 받기
		printf("str : %s\n", str);
//		if (ft_strncmp(str, "exit", 5) == 0) // || (ctrl-d signal)) // 종료 조건
//		{
			// cleaner(str, &ds, NULL);
			// free (str);
//			break ;
//		}
//		else if (SIGINT :ctrl-C signal)
//			printf("\n");
//		else if (ctrl-\ sig)
//			;
		// else
		// {
			add_history(str);
			// printf("input : %s\n", str);
			ds.head_token = tokenize(str); // 2. 토큰화
			if (ds.head_token == NULL)
			{
				free(str);
				continue ;
			}
			if (make_tree(&ds) == 0 || (!tree_parser(ds.root_node, &flag) && flag == 1)) // 2-2. 토큰을 자료구조에 넣는다
			{
				cleaner(str, &ds, NULL);
				continue ;
			}
			printf("\n!ALERT! <after parsing>\n");
			ft_lstiter(ds.head_token, print_content);
			ft_traverse(ds.root_node);
			printf("before excute\n");
			execute(&ds);
		// }
		// heredoc_cleaner(&ds);
		cleaner(str, &ds, NULL);
	}
	// 여기에 환경변수 프리()
	clean_exit(SUCCESS, str, NULL, &ds);
	return (0);
}

//  (1) env export 만들기
//  (2) tree_parser 에 환경변수 들고 들어가게 수정