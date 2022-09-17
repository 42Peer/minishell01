#include "minishell.h"

char	*save(char *src, char c, size_t len);	// 문자열 src에 문자 c 붙이는 함수, len은 src의 길이
void	tree_parser(t_node *node);
void	ft_traverse(t_node *node);

char	**func_heredoc(t_node *node, char *delimiter, int quoted)
{
	int		fd;
	int		i;
	char 	*filename; //
	char	*str;
	char	*expanded_str;
	char	*tmp_str;

	// (1-1) 히어독 여러개 잇을때 다른 파일이름 만들기
	// (1-2) 나중에 실행파트에서 히어독 실행하려면 트리구조에 파일이름을 저장해놔야하는지?
	filename = ft_strdup("/tmp/here_doc_0");
	// (1) tmpfile 만들기
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
	while (fd == -1)
	{
		filename = save(filename, '0', ft_strlen(filename));
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
	}
	// (2) tmpfile에 히어독 받고 확장 유무체크후 처리

	// 1. 델리미터 들고 오기
	// 2. 한라인 읽기 (str = readline. 이때 ">" 출력)
	// 3. 델리미터 인지 확인 
	// 3-1. 델리미터면 반복문 나감 (if str == 델리미터)
	// 4. 확장 필요하면 확장 라인 들고옴 (else)
	// 5. 파일에 쓰기 (개행 붙이기)
	// 6. 2번으로 간다
	while (1)
	{
		expanded_str = NULL;
		str = readline(">");
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (!quoted)
		{
			i = -1;
			while (str[++i])
			{
				if (str[i] == '$')
					expanded_str = ft_strjoin(expanded_str, dollar_sign(str, &i));
				else
					expanded_str = save(expanded_str, str[i], ft_strlen(expanded_str));
			}
			write(fd, expanded_str, ft_strlen(expanded_str));
			write(fd, "\n", 1);
		}
		else
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
		free(str);
		free(expanded_str);
	}
	free(str);
	close(fd);
	// (3) 노드 갱신
	// (3-1) << 노드의 content 의 <로 바꿔주기
	if (node->content)
		free(node->content);
	node->content = ft_strdup("<");
	// (3-2) << 노드의 DELIMITER를 heredoc 임시파일로 바꿔주기
	if (node->right->content)
		free(node->right->content);
	node->right->content = filename;
	return (NULL);
}

void	cmd_parser(t_node *node)
{
	char	*new_content;

	if (!node)
		return ;
	cmd_parser(node->left);
	cmd_parser(node->right);
	if (node->type == T_WORD)
	{
		new_content = delquote(node->content, NULL);
		free(node->content);
		node->content = new_content;
	}
}

void	redir_parser(t_node *node)
{
	int		quoted;
	char	*new_content;

	quoted = 0;		// 기본 0 = 인용 없음 으로 초기화
	if (!node)
		return ;
	if (node->type == T_REDIR)
	{
		if (ft_strncmp(node->content, "<<", 3) == 0)	// heredoc이면
		{
			printf("heredoc 도착!\n");
			printf("delimiter : %s\n", node->right->content);
			new_content = delquote(node->right->content, &quoted);
			free(node->right->content);
			node->right->content = new_content;
			func_heredoc(node, node->right->content, quoted);
		}
	}
	else
	{
		redir_parser(node->right);	// T_REDIR
		redir_parser(node->left);	// 다른 redir
	}
}

void	tree_parser(t_node *node)
{
	if (!(node))
		return ;
	// printf("now node type : %s node str : %s\n", token_str[node->type], node->str);
	if (node->type == N_PHRASE)
	{
		redir_parser(node->left);
		cmd_parser(node->right);
	}
	else
	{
		tree_parser(node->left);	// phrase
		tree_parser(node->right);	// 새 프로세스
	}
}
