
# ---------------------------------------------------------
# 실행부문 수도코드
# pipe - 리디렉션 - 실행 - exitstatus
# ---------------------------------------------------------

리다이렉션 노드 순회(head_process)
{	
	if (노드가 없으면)
		리턴
	리다이렉션 = 노드->컨탠트
	파일 네임 = 노드->오른쪽->컨탠트
	//리다이렉션 처리
	리다이렉션 노드 순회(노드->왼쪽);
}

커맨드 노드 순회(head_process)
{
	if (노드가 없다면)
		리턴
	커맨드 = 노드->컨탠트
	아규먼트 들고 오기
	커맨드 실행
}

트리 노드 순회 처리(head_process)
{
	if(노드가 프레이즈)
	{
		리다이렉션 노드순회(노드->왼쪽);
		커맨드 노드순회(노드->오른쪽);
	}
	else
	{
		트리노드 순회(노드->왼쪽);
		트리노드 순회(노드->오른쪽);
	}
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

메인프로세스(t_struct *ds, envp, int *status)
{
	int storagefd;
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
			storagefd = dup(STDIN);
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
		dup2(0, storagefd);
		waitpid(pid, status) // 마지막 프로세스
		while (프로세스 갯수 -2)
			wait
		sigterm?
	}
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
