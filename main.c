#include "minishell.h"
/*
root
 |
process(pipe)
 |                              \
[       phrase       ]       process(pipe)
 |              |
redirection    cmd
*/

// << hi echo hi > file3 a b c >file2 | wc -l
// 하나의 프로세스 노드에서
// 현재토큰에서
// RIDERIECTION 노드 만들기();

int main(int argc, char **argv, char **envp)
{
	char		*str;
	t_struct	ds;

	ds.head_token = NULL;
	ds.root_node = NULL;
	while (1)
	{
		str = readline("minishell > "); // 1. 입력 받기
		if (strcmp(str, "exit") == 0) // || (ctrl-d signal)) // 종료 조건
			break;
//		else if (SIGINT :ctrl-C signal)
//			printf("\n");
//		else if (ctrl-\ sig)
//			;
		else
		{
			printf("input : %s\n", str);
			ds.head_token = tokenize(str); // 2. 토큰화
			ft_lstiter(ds.head_token, print_content);
//			int i = -1;
//			while (++i < ft_lstsize(head_token))
//				ft_lstiter(head_token, (*printf)("%s\n", head_token->content));
		}
		make_tree(&ds); // 토큰을 자료구조에 넣는다
		ft_traverse(ds.root_node);
		add_history(str);
		free(str);
	}
	clean_exit(SUCCESS, NULL, NULL, &ds);
	return (0);
}
