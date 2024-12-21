#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid, ppid, chpid;
    int a = 0;

    chpid = fork();

    switch (chpid)
    {
        case -1:
	        perror("Fork error");
	        exit(EXIT_FAILURE);
    	case 0:
	        execl("/bin/ls", "ls", "-l", (char *)NULL);
	        fprintf(stderr, "Exec error\n");
	        exit(EXIT_FAILURE);
	    default:
	        printf("Parent\n");
    }

    a = ++a;

    pid  = getpid();
    ppid = getppid();

    printf("Pid = %d\nPpid = %d\nResult = %d\n", (int)pid, (int)ppid, a);

    return 0;
}