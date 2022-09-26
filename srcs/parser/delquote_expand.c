#include "../../minishell.h"

char	*expand_env(char *str, int i, int *cur)
{
	char	*env_key;
	char	*env_value;
	int		len;

	while (is_expandable(str, i))
		++i;
	len = i - *cur - 1;
	env_key = ft_substr(str, (unsigned int)((*cur) + 1), len);
	*cur = i - 1;
	env_value = ft_getenv(env_key);
	free(env_key);
	if (!env_value)
		return (ft_strdup(""));
	return (env_value);
}

char	*dollar_sign(char *str, int *cur)
{
	int		i;

	i = *cur + 1;
	if (str[i] == '\0' || is_whitespace(str[i]))
		return (ft_strdup("$"));
	if (str[i] == '?' && (str[i + 1] == '\0' || is_whitespace(str[i + 1])))
	{
		*cur = i;
		return (ft_strdup(ft_itoa(set_or_get_status(-1))));
	}
	else
		return (expand_env(str, i, cur));
}

char	*single_quote(char *str, int *quote_i, int *quoted_delimit)
{
	char	*piece;
	int		cur;

	cur = *quote_i;
	piece = ft_strdup("");
	while (str[++cur])
	{
		if (str[cur] == '\'')
		{
			if (quoted_delimit)
				*quoted_delimit = 1;
			while (++(*quote_i) < cur)
				piece = save(piece, str[*quote_i], ft_strlen(piece));
			return (piece);
		}
	}
	return (NULL);
}

char	*double_quote(char *str, int *quote_i, int *quoted_delimit)
{
	char	*piece;
	int		cur;

	cur = *quote_i;
	piece = ft_strdup("");
	while (str[++cur])
	{
		if (str[cur] == '"')
		{
			if (quoted_delimit)
				*quoted_delimit = 1;
			while (++(*quote_i) < cur)
			{
				if (str[(*quote_i)] == '$' && !quoted_delimit)
					piece = ft_strjoin(piece, dollar_sign(str, quote_i));
				else
					piece = save(piece, str[*quote_i], ft_strlen(piece));
			}
			return (piece);
		}
	}
	return (NULL);
}

char	*delquote_expand(char *str, int *quoted_delimit)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = ft_strdup("");
	while (str && str[i])
	{
		if (str[i] == '\'')
			ptr = ft_strjoin(ptr, single_quote(str, &i, quoted_delimit));
		else if (str[i] == '"')
			ptr = ft_strjoin(ptr, double_quote(str, &i, quoted_delimit));
		else if (str[i] == '$' && !quoted_delimit)
			ptr = ft_strjoin(ptr, dollar_sign(str, &i));
		else
			ptr = save(ptr, str[i], ft_strlen(ptr));
		++i;
	}
	return (ptr);
}
