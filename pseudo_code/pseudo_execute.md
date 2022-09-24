
# ---------------------------------------------------------
# 실행부문 수도코드
# pipe - 리디렉션 - 실행 - exitstatus
# ---------------------------------------------------------

리다이렉션 처리(노드)
{
	if (노드 타입 == T_히어독)
	{
		히어독 리다이렉션 처리
		언링크
	}
	else //노드 타입이 T_리다이렉트
	{
		일반 파일 리다이렉션 처리
	}
}

커맨드 처리(노드)
{
	환경변수 들고오기
	커맨드 아규먼트 2차원 배열로 만들기
	경로 만들기
	execve();
}

자식 프로세스 처리(head_process)
{
	if (노드가 없다면)
		return
	자식 프로세스 처리 (노드->왼쪽);
	if (노드가 io_redir)
		리다이렉트 처리(노드->오른쪽);
	else if (노드가 phrase)
		커맨드 처리(노드->오른쪽);
	else
		printf("Not comming here!!");
}

자식프로세스 명령어 실행(head_process, envp, int *fd)
{
	head_process부터 트리를 순회하면서
	----- (1) 리디렉션 노드를 전부 순회하며 리디렉션처리()------
	리다이렉션 노드 순회 처리();
	----- (2) 커맨드 노드로 와서 ARGS 만들기 --------------
	커맨드 노드 순회 처리();
	----- (3) 실행  ----------------------------------
	PATH = 로컬폴더 혹은 빌트인 PATH를 찾아줘서 넣기
	if (path 가 있다면)
		execve(PATH, ARGS, ENVP);
	else if (빌트인이라면)
	{
		if (빌트인함수() != 정상종료);
			exit(에러상태)
		exit(0);
	}
	-------------------------------------------------
}

int		cmd가 빌트인인지 확인하는 함수(tree head)
{
	node = node->left;	// phrase
	node = node->right;	// cmd
	if (node->type == T_WORD)
	{
		if (ft_strncmp(node->content, "cd", 3) == 0
			|| ft_strncmp(node->content, "pwd", 4) == 0
			|| ft_strncmp(node->content, "export", 7) == 0
			|| ft_strncmp(node->content, "env", 4) == 0
			|| ft_strncmp(node->content, "exit", 5) == 0)
			return (1);
		return (0);
	}
}

char	**ft_2Dstrdup(t_node *args)
{
	char	**ptr;
	int		i;

	i = -1;
	ptr = malloc(sizeof(char *) * ft_lstsize(args));
	while (args)
	{
		ptr[++i] = ft_strdup(args->content);
		args = args->right;
	}
	return (ptr);
}

void	main에서 실행함수_ls (t_struct *ds, void (*f)(char **))
{
	char	*cmd;
	char	**args;
	int status;

	cmd = ft_strdup(ds->left->right);
	args = ft_2dstrdup(ds->left->right->right);
	status = status_error(error);
	if (!ft_strncmp(cmd[0], "ls", 3))
		ft_ls(, status);
	else if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(, status);
	else if (pwd)
		ft_pwd();
	... cd export unset env exit
	free(cmd);
}

fork 후 실행함수(t_struct *ds)
{
	int storage_fd;

	storage_fd = dup(STDIN);
	while (프로세스의 갯수 - 1 만큼)
	{
		int fd[2];
		pipe(fd);
		pid = fork();
		if (자식프로세스면)
		{
			close(fd[0])
			dup2(fd[1], STDOUT);
			close(fd[1]);
			자식프로세스 명령어 실행(cur_process, evnp);
		}
		else if (부모프로세스면)
		{
			close(fd[1])
			dup2(fd[0], STDIN)
			close(fd[0]);
		}
		cur_process = cur_process->right
	}
	pid = fork();
	if (자식프로세스)
	{
		자식프로세스 명령어 실행(cur_process, evnp);
	}
	else (부모프로세스)
	{
		dup2(0, storage_fd);
		waitpid(pid, status) // 마지막 프로세스
		while (프로세스 갯수 -2)
			wait
		sigterm?
		dup2(storagefd, STDIN);
	}
}

void	execute(t_struct *ds)
{
	if (!(head->right) && cmd가 빌트인인지 확인하는 함수(ds->root_node))
		if main에서 실행함수(ds);
	else
		fork 후 실행함수();
}

# 확장시 추가 처리 해줘야함.
# $? <- 이거 환경변수에 없음.
# status 로 확장
# (1) built-in 유무 따지기
# (2) 절대경로 or 상대경로 판단
void	get_ps(t_struct *ds, char **envp)
{
    int     size;
    int     count;

    count = 0;
    프로세스갯수 = ft_lstsize(ds->root_node->right) + 1;
    while (count++ <= 프로세스갯수)
	{
		if (count == )
			fork_frame(ds->root_node->right, envp, outfile, END);
		else
			fork_frame(ds->root_node->right, envp, outfile, CONTINUE);
	}
	while (--count >= 0)
		waitpid(-1, 0, 0);
}
