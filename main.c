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
// CMD 노드만들기();
// RIDERIECTION 노드 만들기();

create_process_node()
{
	t_token	*head;
	t_token	*process_node;

	process_node = malloc;
	head = process_node;
	process_node->left = create_phrase_node();

	return (head);
}

create_phrase_node()
{
	t_token	*phrase;
	
	phrase = malloc;
	phrase->left = malloc;
	phrase->right = malloc;

	return (phrase);
}

put_token_cmd(t_token	*process, t_token *p_token)
{
	t_token	*cur_cmd;

	cur_cmd = process->left->right;			// 커서를 트리의 cmd 노드까지
	if (cur_cmd->cmd_token.content == NULL) 	// cmd 토큰이 없으면
		cur_cmd->cmd_token = *p_token;
	else										// cmd 토큰이 있으면
	{
		arg_token[] 비는 곳에 토큰 추가
		cur_cmd->arg_token[] = *p_token;
	}
}

put_token_redir(t_token	*process, t_token *p_token)
{
	t_token	*cur_redir;

	cur_redir = process->p_phrase->p_redir;
	while (cur_redir->next == NULL)		// 가장 끝 리디렉션 노드까지 커서 이동
		cur_redir = cur_redir->next;
	if (토큰이 있으면)
		리디렉션 노드 추가();
		커서 = 커서->넥스트;
	else
	{
		cur_redir.redir_token = token++;
		cur_redir.arg_token = token;
	}
}

t_token	*put_struct(t_token *head, t_token *p_token)
{
	t_token	*head;
	t_token	*cur;

	head = create_process_node();
	cur = head;
	while (토큰이 끝날때까지)
	{
		if (토큰 == WORD)
		{
			put_token_cmd(cur, 토큰);
		}
		else if (토큰 == REDIR)
		{
			put_token_redir(cur, 토큰);
		}
		else if (토큰 == PIPE)
		{
			create_process_node(cur, 토큰);
			cur = head->next;
		}
		++토큰;
	}
	return (head);
}

/*int main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token *root;
	t_token	head_token;

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
			head_token = tokenize(str); // 2. 토큰화
			printf("input : %s\n", str);
		root = make_tree(head_token); // 토큰을 자료구조에 넣는다
		add_history(str);
		free(str);
	}
	return(0);
}
*/
void	echo(char **str) // 가변으로 받기
{
	int	i;

	i = -1;
	if (str[0][++i] == '-')
	{
		while (str[0][++i] == 'n');	// ???? -nnnnnnnnnnnnabc
		if (str[0][i] == '\0') // -n 옵션이 있을 때
		{
			int j = -1;
			while (str[++j])
			{
				if (j != max)
					printf("%s ", str[j]);
				else
					printf("%s", str[j]);
			}		
		}
		else
		{
			int j = -1;
			while (str[++j])
				if (j != max)
					printf("%s", str[j]);
			printf("\n");
		}
	}
	else
	{
		str 들 이어 붙이기.
		printf("%s\n", str);
	}
}

void	pwd(void)//getcwd
{
	// char *getcwd(char *buf, size_t size);
	char *path;
	char path[1024];//크기 어떻게?

	getcwd(path, 1024);
	printf("working directory : %s\n", path);
}
// 	path = PATH찾기.
//pwd 다음에 오는 word는 다 문자 처리. ex) '