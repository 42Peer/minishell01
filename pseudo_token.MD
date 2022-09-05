#
# int main(int argc, char **argv, char **envp)
# {
#	char	*str;
#	t_process *root;
#	t_token	head_token;
#
#	while (1)
#	{
#		str = readline("minishell > "); // 1. 입력 받기
#		if (strcmp(str, "exit") == 0 || (ctrl-d signal)) // 종료 조건
#			break;
#		else if (SIGINT :ctrl-C signal)
#			printf("\n");
#		else if (ctrl-\ sig)
#			;
#		else
#			head_token = tokenizing(str); // 2. 토큰화
#			printf("input : %s\n", str);
#		root = make_tree(head_token); // 토큰을 자료구조에 넣는다
#		add_history(str);
#		free(str);
#	}
#	return(0);
# }

# t_token	head_token;
# head_token = tokenizing(str); // 2. 토큰화

t_token tokenize(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (인용중이지 않음 && 이전 문자가 연산자의 일부)	// 2,3
		{
			if (현재 위치가 연산자의 일부로 사용 가능)
				토큰 저장(start ~ 현재 인덱스, 토큰 타입) //
			else (현재 위치가 연산자의 일부로 사용불가)
				토큰 저장(start ~ 이전 문자 인덱스, 토큰 타입)
		}
		else if (인용중이지 않음 && (현재 인덱스 == ''' || 현재 인덱스 == '"'))		// 4
		{
			인용플래그 == 1;
			if (토큰 타입 == NONE)
			{
				시작 인덱스 = 현재 인덱스;
				토큰 타입 = WORD;
			}
		}
		else if (인용중이지 않음 && 현재 인덱스 == is_operator(str[i]))		// 6
		{
			토큰 저장(시작 인덱스 ~ 이전 문자, 토큰 타입);
			시작 인덱스 = 현재 인덱스;
			if (현재 인덱스 == '|')
				토큰 타입 = PIPE;
			else
				토큰 타입 = REDIR;
		}
		else if (인용중이지 않음 && 현재 인덱스 == ' ')		// 8
			토큰 저장(시작 인덱스 ~ 이전 문자(현재 인덱스 - 1), 토큰 타입);
			토큰 타입 = NONE;
		else if (시작 인덱스 != 현재 인덱스)		// 9
		{
			if (인용중 && (현재 인덱스 == ''' || 현재 인덱스 == '"'))
				인용 플래그 = 0;
		}
		else		// 11. 현재 문자가 새로운 단어의 시작
			printf("<else> %c\n", str[i]);
			시작 인덱스 = 현재 인덱스;
			토큰 타입 = WORD;
        i++;
	}
	// 1
	if (토큰 타입 != NONE) // 토큰 만드는 중이라면
		토큰 저장(시작 인덱스 ~ 이전 문자(현재 인덱스 - 1), 토큰 타입);
	else (토큰 타입 == NONE) // 토큰이 없다면
		end-of-input-indicator 토큰 반환 : 아무것도 하지 않음
}

/* 도움말 */
토큰 구분될 때 토큰 시작 인덱스 ~ 현재 인덱스까지 저장;
토큰 저장 : add_list_last;
(인용 플래그) quoted = 0 (1은 인용중, 0은 아님)
operator로 인식 되는 경우 : <, >, <<, >>, |

if (*str == '<')
    if (*(str + 1) == '<')
        here_doc();

# << "LIMITER"         <- 자료구조 삽입후 인용-히어독-확장-리디렉션 단계에서 처리
> 구분자가 인용된 경우 -> 인용 제거 수행 + here-doc 행은 확장되지 않음
> 구분자가 인용되지 않은 경우 -> here-doc 행은 모두 확장됨