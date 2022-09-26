#include "../../minishell.h"

static int	ft_word_count(char const *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c)
		{
			++cnt;
			while (*str != c && *str)
				++str;
		}
		while (*str == c && *str)
			++str;
	}
	return (cnt);
}

static char	**ft_free_array(char **array, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}

static char	**ft_put_array(char **array, char const *str, char c)
{
	char	*wd_start;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			wd_start = &(*(char *)str);
			while (*str && *str != c && ++word_len)
				++str;
			array[i] = (char *)malloc(sizeof(char) * (word_len + 1));
			if (array[i] == NULL)
				return (ft_free_array(array, i));
			ft_strlcpy(array[i], wd_start, word_len + 1);
			++i;
			word_len = 0;
		}
		else if (*str == c)
			++str;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_cnt;

	if (s == NULL)
		return (NULL);
	word_cnt = ft_word_count(s, c);
	array = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (array == NULL)
		system_call_error(ALLOC_FAIL);
	array[word_cnt] = 0;
	array = ft_put_array(array, s, c);
	return (array);
}
