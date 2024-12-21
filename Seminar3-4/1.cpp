#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main ()
{
	printf("%d\n%d\n", getpid(), getppid());
}

