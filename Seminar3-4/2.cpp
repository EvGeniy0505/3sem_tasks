#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, ppid, chpid;

    int a = 0;

    chpid = fork();

    a = ++a;

    pid  = getpid();
    ppid = getppid();

    printf("Pid = %d\nPpid = %d\nResult = %d\n", pid, ppid, a);

    return 0;
}