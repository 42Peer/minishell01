#include "../../minishell.h"

void	info_init(t_token_info *info)
{
	info->start_idx = 0;
	info->cur_idx = 0;
	info->sin_quoted = 0;
	info->dou_quoted = 0;
	info->double_piped = 0;
	info->token_type = NONE;
	info->token_list = NULL;
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
	if (is_case_token_syntax_error(&info))
		return (NULL);
	if (info.token_type != NONE)
		make_token(str, info.cur_idx - 1, &info);
	return (info.token_list);
}
