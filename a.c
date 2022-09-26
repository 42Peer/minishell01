#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv, char **envp)
{
	char **two_d;

	two_d = malloc(sizeof(char *) * 2);
	two_d[0] = malloc(sizeof(char) * 5);
	two_d[1] = malloc(sizeof(char) * 5);
	free (two_d[0]);
	free (two_d[1]);
	free (two_d);
	system("leaks a.out");
}
/*
	char *path = "-";
	char dir[30] = "Current Directory : ";
	int ch = chdir(path);

	if (ch == 0)//chdir 성공
		printf("Changed directory\n"); // 디렉 이동 성공
	else
		printf("Failed changing directory\n");
	
	write(1, dir, sizeof(char) * strlen(dir));
	char buf[100];
	getcwd(buf, 100);
	printf("현재 디렉 : %s\n", buf);
}
	*/
