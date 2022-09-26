#include "../minishell.h"

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
