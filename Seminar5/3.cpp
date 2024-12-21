#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int     fd;
    size_t  size;
    char    string[] = "Hello, world!";

    if((fd = open("myfile2", O_WRONLY | O_CREAT, 0666)) < 0)
    {
        printf("Can\'t open file\n");
        exit(-1);
    }

    size = read(fd, string, 100);

    if(size < 0){
        printf("Can\'t read all string\n");
        exit(-1);
    }

    if(close(fd) < 0)
    {
        printf("Can\'t close file\n");
    }

    size = write(1, string, 100);

    if(size < 0)
    {
         printf("Can\'t write all string\n");
         exit(-1);
    }

    return 0;
}