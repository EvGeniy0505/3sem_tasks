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

    // Устанавливаем маску создания файла, чтобы она не влияла на права доступа к файлу
    (void)umask(0);

    // Открываем файл "myfile2" для записи, создавая его если он не существует
    // Права доступа к файлу устанавливаются как 0666 (чтение и запись для всех)
    if((fd = open("myfile2", O_WRONLY | O_CREAT, 0666)) < 0)
    {
        printf("Can\'t open file\n");
        exit(-1);
    }

    // Записываем строку в файл
    size = write(fd, string, 14);

    // Если запись не удалась или было записано не все, выводим сообщение об ошибке и завершаем программу
    if(size != 14){
        printf("Can\'t write all string\n");
        exit(-1);
    }

    if(close(fd) < 0)
    {
        printf("Can\'t close file\n");
    }

    return 0;
}