
# minishell make_tree sudo code
# type : word token, pipe token(|), redir token (<<, >>, <, >)
# phrase : 파이프 제외(redirection 포함)
# 자료구조삽입

# define으로 type 매크로 지정해줘야함

t_token	*프로세스 만들기(t_token *head)
{
	t_token	*cur;p

	head = calloc;
	head->type = N_PROCESS;
	cur = head;
	cur->left = calloc;			// phrase node
	cur->left->type = N_PHRASE;
	cur = cur->left;			// phrase node로 커서 이동
	cur->left = calloc;			// redir node;
	cur->left->type = N_REDIR;

	return (head);
}

/* 파이프 추가하기 */
프로세스 만들기(head->right);

t_token head_token;
int main에서 root = make_tree(head_token); 트리만들기함수로 받아옴

phrase 만들기
{
	phrase 노드 만들기
	redir 노드 만들기
	cmd 노드 만들기
	phrase 노드가 redir노드 연결
	phrase 노드가 cmd 노드 연결
}

t_token *프로세스(파이프라인)만들기함수()
{
	process(pipeline) 노드 만들기;
	phrase만들기함수();
	return
}

t_token io_redir(토큰)
{
	io_redir 노드 만들기
	redir 노드에 io_redir노드 연결
	io_redir 노드 왼쪽에 리다이렉션 토큰 붙이기
		토큰 = 토큰->next;
	리다이렉션 토큰 아래에 WORD 토큰(Limiter) 붙이기
	return (토큰)
}

t_token yichoi_cmd(토큰, t_token*)
{
    t_token = lst_add_back(token->content를 cmd->cmd_token 에 넣는다);
	토큰 = 토큰->next;
    return (token);
}

t_token *make_tree(t_token head_token)
{
	t_token *head_process;
	t_token *cur;
	
	head_process = 프로세스(파이프라인)만들기함수
	cur = head_process;
	while (토큰 끝날때까지)
	{
		if (토큰의 종류 == redir)
			토큰 = io_redir 함수에 들어가서 그 함수 안에서 노드만들기
		else if (토큰의 종류 == cmd)
            토큰 = yichoi_cmd();
		else if (토큰의 종류 == pipe)
			make_tree 함수(head_process->next);
			cur = cur->next;	// 다음 파이프라인으로 커서 옮기기
			++토큰;
	}
	return (head_process);
}



# < 트리순서 >
# 루트 만들기
# 프레이즈 만들기
# 커맨드 만들기
# 리다이렉션 만들기
# 토큰 type 파악
# if (토큰 == 커맨드)
#	커맨드 찾기
#	커맨드에 넣기
# 첫번째
# else if (토큰 == 리다이렉션)
# 	리다이렉션 찾기
# 	리다이렉션에 넣기
# 파이프라인이 있다면 루트로 올라가서 파이프 만들기

# hi echo << hi >> file3 | gg cat <file1
# << hi echo 
# << 일 경우, 에러처리 어디서? 토크나이즈 - 에러처리 - 자료구조삽입 - 인용등 처리