// main 문에서 make_tree 어떻게 되어있는지
// root = make_tree(head_token); // 토큰을 자료구조에 넣는다

#include "minishell.h"

t_token	*make_tree(t_token *head_token)
{
	t_token	*root;
	t_token	*cur_tree;
	t_token *cur_token;

	cur_token = head_token;
	root = make_process();
	cur_tree = root;
	while (cur_token)
	{
		if (cur_token->type == N_REDIR)

		else if (cur_token->type == N_PROCESS)
		else // cmd일때
		cur_token = cur_token->next;
	}
	return (root);
}
