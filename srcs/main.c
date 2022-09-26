#include "../minishell.h"

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
	if (!s1)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!copy)
		system_call_error(ALLOC_FAIL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
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

void	main_init(int *p_flag, t_struct *p_ds, )
{

}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;
	int			flag;

	flag = 0;
	ds.head_token = NULL;
	ds.root_node = NULL;
	if (argc)
		(void)argv;
	make_env_array(envp);
	while (1)
	{
		signal_handler();
		str = readline("minishell > ");
		if (!str)
			exit(130);
		in_process_signal_handler();
		add_history(str);
		ds.head_token = tokenize(str);
		if (ds.head_token == NULL)
		{
			free(str);
			continue ;
		}
		if (make_tree(&ds) == 0
			|| (!tree_parser(ds.root_node, &flag) && flag == 1))
		{
			cleaner(str, &ds, NULL);
			continue ;
		}
		execute(&ds);
		cleaner(str, &ds, NULL);
	}
	return (0);
}
