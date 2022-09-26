#include "../minishell.h"

char	*dollar_sign(char *str, int *env_i)
{
	char	*env_key;
	int		i;
	int		len;

	i = *env_i + 1;
	if (str[i] == '\0' || is_whitespace(str[i]))
		return (ft_strdup("$"));
	if (str[i] == '?' && (str[i + 1] == '\0' || is_whitespace(str[i + 1])))
	{
		*env_i = i;
		return (ft_strdup(ft_itoa(set_or_get_status(-1))));
	}
	else
	{
		while (is_expandable(str, i))
			++i;
		len = i - *env_i - 1;
		env_key = ft_substr(str, (unsigned int)((*env_i) + 1), len);
		*env_i = i - 1;
		if (!ft_getenv(env_key))
			return (ft_strdup(""));
		else
			return (ft_getenv(env_key));
	}
}

char	*single_quote(char *str, int *quote_i, int *quoted)
{
	char	*piece;
	int		env_i;
	int		douq_i;
	int		i;

	i = *quote_i;
	env_i = 0;
	douq_i = 0;
	piece = ft_strdup("");
	while (str[++i])
	{
		if (!env_i && str[i] == '$')
			env_i = i;
		if (!douq_i && str[i] == '"')
			douq_i = i;
		if (str[i] == '\'')
		{
			if (quoted)
				*quoted = 1;
			while (++(*quote_i) < i)
				piece = save(piece, str[*quote_i], ft_strlen(piece));
			return (piece);
		}
	}
	if ((douq_i && env_i && douq_i < env_i) || (douq_i && !env_i))
		i = douq_i;
	else if ((douq_i && env_i && douq_i > env_i) || (!douq_i && env_i))
		i = env_i;
	while (*quote_i < i)
		piece = save(piece, str[(*quote_i)++], ft_strlen(piece));
	--(*quote_i);
	return (piece);
}

char	*double_quote(char *str, int *quote_i, int *quoted)
{
	char	*piece;
	int		env_i;
	int		sigq_i;
	int		i;

	i = *quote_i;
	env_i = 0;
	sigq_i = 0;
	piece = ft_strdup("");
	while (str[++i])
	{
		if (!sigq_i && str[i] == '\'')
			sigq_i = i;
		else if (!env_i && str[i] == '$')
			env_i = i;
		else if (str[i] == '"')
		{
			if (quoted)
				*quoted = 1;
			while (++(*quote_i) < i)
			{
				if (str[(*quote_i)] == '$' && !quoted)
					piece = ft_strjoin(piece, dollar_sign(str, quote_i));
				else
					piece = save(piece, str[*quote_i], ft_strlen(piece));
			}
			return (piece);
		}
	}
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
		else if (str[i] == '$' && !quoted)
			ptr = ft_strjoin(ptr, dollar_sign(str, &i));
		else
			ptr = save(ptr, str[i], ft_strlen(ptr));
		++i;
	}
	return (ptr);
}
