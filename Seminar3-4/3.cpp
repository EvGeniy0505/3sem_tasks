#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid, ppid, chpid;
    int a = 0;

    chpid = fork();

    if (chpid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (chpid == 0)
    {
	    printf("Child\n");
	    a += 57;
    }
    else
    {
	    printf("Parent\n");
	    a += 52;
    }

    pid  = getpid();
    ppid = getppid();

    printf("Pid = %d\nPpid = %d\nResult = %d\n", pid, ppid, a);

    return 0;
}