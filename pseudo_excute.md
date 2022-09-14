
# ---------------------------------------------------------
# 실행부문 수도코드
# pipe - 리디렉션 - 실행 - exitstatus
# ---------------------------------------------------------

자식프로세스 명령어 실행(head_process, envp, int *fd)
{
	head_process부터 트리를 순회하면서
	----- (1) 리디렉션처리(); --------------------------
	----- (2) ARGS 만들기(head_process); -------------
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

메인프로세스(envp)
{
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
		waitpid(pid) // 마지막 프로세스
		while (프로세스 갯수 -1)
			wait
	}
}


