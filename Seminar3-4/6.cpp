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
	    fprintf(stderr, "Fork fail\n");
	    exit(EXIT_FAILURE);
    }

    if (chpid == 0)
    {
        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec failed");
	    exit(EXIT_FAILURE);
    }
    else
    {
	    printf("Parent\n");
    }

    a = ++a;

    pid  = getpid();
    ppid = getppid();

    printf("Pid = %d\nPpid = %d\nResult = %d\n", (int)pid, (int)ppid, a);

    return 0;
}