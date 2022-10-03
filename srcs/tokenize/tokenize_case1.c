#include "../../minishell.h"

void	case_part_of_operator(char *str, t_token_info *info)
{
	if (is_operator(str[info->cur_idx]))
	{
		if (str[info->cur_idx - 1] == '|' && str[info->cur_idx] == '|')
			info->double_piped = 1;
		make_token(str, info->cur_idx, info);
	}
	else
	{
		make_token(str, info->cur_idx - 1, info);
		if (!is_whitespace(str[info->cur_idx]))
		{
			if (str[info->cur_idx] == '\'')
				info->sin_quoted = 1;
			else if (str[info->cur_idx] == '"')
				info->dou_quoted = 1;
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
