#include "../minishell.h"

void	info_init(t_token_info *info)
{
	info->start_idx = 0;
	info->cur_idx = 0;
	info->sin_quoted = 0;
	info->dou_quoted = 0;
	info->token_type = NONE;
	info->token_list = NULL;
}

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

int	make_token(char *str, int copy_idx, t_token_info *info)
{
	char	*copy;
	size_t	len;
	t_token	*token;

	if ((str == NULL) || (info == NULL))
		return (ERROR);
	len = copy_idx - info->start_idx + 1;
	copy = ft_calloc(len + 1, sizeof(char));
	if (!copy)
		system_call_error(ALLOC_FAIL);
	ft_memcpy(copy, str + info->start_idx, len);
	token = ft_lstnew(info->token_type, copy);
	ft_lstadd_back(&(info->token_list), token);
	info->token_type = NONE;
	return (0);
}

void	case_part_of_operator(char *str, t_token_info *info)
{
	if (is_operator(str[info->cur_idx]))
		make_token(str, info->cur_idx, info);
	else
	{
		make_token(str, info->cur_idx - 1, info);
		if (!is_whitespace(str[info->cur_idx]))
		{
			info->start_idx = info->cur_idx;
			info->token_type = T_WORD;
		}
	}
}

void	case_quote_start(char chr, t_token_info *info)
{
	if (chr == '\'')
		info->sin_quoted = 1;
	else if (chr == '"')
		info->dou_quoted = 1;
	if (info->token_type == NONE)
	{
		info->start_idx = info->cur_idx;
		info->token_type = T_WORD;
	}
}

void	case_operator(char *str, t_token_info *info)
{
	if (info->token_type != NONE)
		make_token(str, info->cur_idx - 1, info);
	info->start_idx = info->cur_idx;
	if (str[info->cur_idx] == '|')
		info->token_type = T_PIPE;
	else
		info->token_type = T_REDIR;
}

void	case_blank(char *str, t_token_info *info)
{
	if (info->token_type != NONE)
		make_token(str, info->cur_idx - 1, info);
}

void	case_part_of_word(char *str, t_token_info *info)
{
	if (info->sin_quoted && str[info->cur_idx] == '\'')
		info->sin_quoted = 0;
	else if (info->dou_quoted && str[info->cur_idx] == '"')
		info->dou_quoted = 0;
}

void	case_new_word(t_token_info *info)
{
	info->start_idx = info->cur_idx;
	info->token_type = T_WORD;
}

int	is_unquoted(t_token_info *info)
{
	if (info->sin_quoted || info->dou_quoted)
	{
		printf("WARNING: syntax error! unquoted!\n");
		set_or_get_status(SYNTAX_ERROR);
		cleaner(NULL, NULL, info->token_list);
		return (1);
	}
	return (0);
}

void	token_search(char *str, t_token_info *info)
{
	if ((!info->sin_quoted && !info->dou_quoted)
		&& ((info->token_type == T_REDIR || info->token_type == T_PIPE)))
		case_part_of_operator(str, info);
	else if ((!info->sin_quoted && !info->dou_quoted)
		&& is_quote(str[info->cur_idx]))
		case_quote_start(str[info->cur_idx], info);
	else if ((!info->sin_quoted && !info->dou_quoted)
		&& is_operator(str[info->cur_idx]))
		case_operator(str, info);
	else if ((!info->sin_quoted && !info->dou_quoted)
		&& is_whitespace(str[info->cur_idx]))
		case_blank(str, info);
	else if (info->token_type == T_WORD)
		case_part_of_word(str, info);
	else
		case_new_word(info);
}

t_token	*tokenize(char *str)
{
	t_token_info	info;

	info_init(&info);
	while (str[info.cur_idx])
	{
		token_search(str, &info);
		++info.cur_idx;
	}
	if (is_unquoted(&info))
		return (NULL);
	if (info.token_type != NONE)
		make_token(str, info.cur_idx - 1, &info);
	return (info.token_list);
}
