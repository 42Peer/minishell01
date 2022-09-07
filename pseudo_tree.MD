
# minishell make_tree sudo code
# type : word token, pipe token(|), redir token (<<, >>, <, >)
# phrase : 파이프 제외(redirection 포함)
# 자료구조삽입
# define으로 type 매크로 지정해줘야함


/* 파이프 추가하기 */
프로세스 만들기(head->right);

t_token head_token;
int main에서 root = make_tree(head_token); 트리만들기함수로 받아옴

t_token io_redir(토큰)
{
	redir 노드 만들기
	redir 노드 왼쪽에 리다이렉션 토큰 붙이기
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

t_token	*프로세스 만들기(t_token *head)
{
	t_token	*cur;

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

phrase 만들기
{
	phrase 노드 만들기
	//redir 노드 만들기
	phrase 노드가 redir노드 연결
}

t_token *프로세스(파이프라인)만들기함수()
{
	process(pipeline) 노드 만들기;
	phrase만들기함수();
	redir 노드 만들기
	return
}

# [token1]-[token2]- ... -[token_n] 
#     ^ 여기부터 하나씩 while을 돌며 토큰 삽입

t_token *make_tree(t_token *head_token)
{
	t_token *root;
	t_token *cur_tree;
	t_token *cur_token;

	root = 프로세스(파이프라인)만들기함수
	cur_tree = root;
	cur_token = head_token;
	while (토큰 끝날때까지)
	{
		if (토큰의 종류 == redir)
			토큰 = io_redir 함수에 들어가서 그 함수 안에서 노드만들기
		else if (토큰의 종류 == pipe)
			make_tree 함수(root->next);
			cur = cur->next;	// 다음 파이프라인으로 커서 옮기기
			++토큰;
		else //(토큰의 종류 == cmd)
            토큰 = yichoi_cmd();
	}
	return (root);
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

t_token	*redir노드만들기(t_node *cur_process, t_token *cur_token)
{
	t_node *io_redir;
	t_node *cur_node;
	t_node *new_node;
	int		i;

	io_redir = ft_calloc(1, sizeof(t_node));
	io_redir->type = N_REDIR;	
	cur_node = cur_process->left; //	
#	// cur_node는 phrase를 가리킴
	while (cur_node->left)
		cur_node = cur_node->left;
#	// cur_node 는 io_redir의 끝을 가리킴
	cur_node->left = io_redir;
#	// 연결
	cur_node = cur_node->left;
#	// cur_node 는 현재 작업중인 io_redir
	i = -1;
	while (++i < 2)
	{
		new_node = ft_calloc(1, sizeof(t_node));
		cur_node->right = new_node;
		new_node->type = cur_token->type;
		new_node->content = cur_token->content;
		cur_token = cur_token->next;
		cur_node = cur_node->right;
	}
	return (cur_token);
}

t_token	*cmd노드만들기(t_node *cur_process, t_token *cur_token)
{
	t_node *cur_node;
	t_node *cmd_node;

	cur_node = cur_process->left;
#		// cur_node 는 phrase를 가리킴
	while (cur_node->right)
		cur_node = cur_node->right;
#		// cur_node 는 cmd노드의 끝을 가리킴
	cmd_node = ft_calloc(1, sizeof(t_node));
	cur_node->right = cmd_node;
#		// 연결 시켜줌.
	cmd_node->type = cur_token->type;
	cmd_node->content = cur_token->content;
	return (cur_token->next);
}
# token free할때 content랑 type double free 안되게,만약 content==NULL이면 free 안되는 방식으로.
# //ex)cat a <<hi b c cmd 토큰 바로 뒤의 것들 한번에 붙이면 안되는 예시

# [token1]-[token2]- ... -[token_n]
# [  <<  ]-[   hi ]-[ | ]-[   cat ]
#     ^ 여기부터 하나씩 while을 돌며 토큰 삽입


t_token	*process노드만들기(t_node **cur_process, t_token *cur_token)
{
	(*cur_process)->right = 기본제공노드만들기();
	*cur_process = (*cur_process)->right;
	return (cur_token->next);
}

t_node *기본제공노드만들기(void)
{
	t_node *process;
	t_node *phrase;

	process = ft_calloc(1, sizeof(t_node));//프로세스 노드 만들기
	process->type = N_PROCESS;
	phrase = ft_calloc(1, sizeof(t_node));
	phrase->type = N_PHRASE;
	process->left = phrase;
	return (process);
}

t_node *make_tree(t_token *head_token)
{
	t_node 	*root;
	t_node 	*cur_process;
	t_token *cur_token = head_token;

	root = 기본제공노드만들기();
	cur_process = root;
	while (cur_token)
	{
		if (cur_token->type == T_REDIR)
			cur_token = redir노드만들기(cur_process, cur_token);
		else if (cur_token->type == T_PIPE)
			cur_token = process노드만들기(&cur_process, cur_token);//+process간 연결해줘야함
		else // (현재 토큰이 cmd 인 상황)
			cur_token = cmd노드만들기(cur_process, cur_token); //+cmd노드 밑에 토큰 붙이기
	}
	return (root);
}

void	ft_free(t_node *root, int status)
{
	while (root->next)
	{
		free(root->next); ?
	}
	if (status)
		exit (ERROR);
	else
		exit (0);
}

void	m_calloc(t_node *process, t_node *root)
{
	t_node new = ft_calloc();
	if (!new)
		return (get_error());
}
