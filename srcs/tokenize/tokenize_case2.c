#include "../../minishell.h"

void	case_new_word(t_token_info *info)
{
	info->start_idx = info->cur_idx;
	info->token_type = T_WORD;
}

int	is_case_unquoted(t_token_info *info)
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
