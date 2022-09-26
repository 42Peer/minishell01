#include "../../minishell.h"

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

char	*ft_getenv(char *key)
{
	char	**split;
	char	*value;
	int		i;
	int		j;

	value = NULL;
	i = -1;
	while (env_array[++i] && !value)
	{
		split = ft_split(env_array[i], '=');
		if (ft_strncmp(split[0], key, ft_strlen(key) + 1) == 0)
			value = ft_strdup(split[1]);
		j = -1;
		while (split[++j])
			free(split[j]);
		free(split);
	}
	return (value);
}

char	*save(char *src, char c, size_t len)
{
	char	*dst;

	if (!src)
		src = ft_strdup("");
	dst = malloc(sizeof(char) * (len + 2));
	if (!dst)
		system_call_error(ALLOC_FAIL);
	ft_strlcpy(dst, src, len + 1);
	dst[len] = c;
	dst[len + 1] = '\0';
	free(src);
	src = NULL;
	return (dst);
}
