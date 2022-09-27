#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	while (1)
	{
		printf("%d\n", i);
		i++;
		sleep(1);
	}
}