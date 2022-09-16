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

void	tree_parser(t_node *node);

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}


char	*ft_strdup(char *s1)
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
		return (NULL);
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
		return (NULL);
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
	int	i = 0;

	ds.head_token = NULL;
	ds.root_node = NULL;
	while (1)
	{
		str = readline("minishell > "); // 1. 입력 받기
		if (strcmp(str, "exit") == 0) // || (ctrl-d signal)) // 종료 조건
		{
			free (str);
			break ;
		}
//		else if (SIGINT :ctrl-C signal)
//			printf("\n");
//		else if (ctrl-\ sig)
//			;
		else
		{
			add_history(str);
			// printf("input : %s\n", str);
			ds.head_token = tokenize(str); // 2. 토큰화
			if (ds.head_token == NULL)
			{
				free(str);
				continue ;
			}
			// ft_lstiter(ds.head_token, print_content);
			make_tree(&ds); 	// 2-2. 토큰을 자료구조에 넣는다
			ft_traverse(ds.root_node);	// delquote 적용 전
			printf("\n<tree parsing...>\n");
			tree_parser(ds.root_node);
			printf("\n<after deleting>\n");
			ft_traverse(ds.root_node);	// delquote 적용 후
			// int i = -1;
			// while (++i < ft_lstsize(ds.head_token))
			// 	ft_lstiter(head_token, (*printf)("%s\n", head_token->content));
		}
		cleaner(str, &ds, NULL);
	}
	//clean_exit(SUCCESS, NULL, NULL, &ds);
	return (0);
}
