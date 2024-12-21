#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Массивы для хранения файловых дескрипторов каналов
    // fd_p2c - канал от родителя к ребенку
    // fd_c2p - канал от ребенка к родителю
    int    fd_p2c[2], fd_c2p[2];
    // Переменная для хранения результата вызова функции fork
    int    result;
    // Переменная для хранения количества прочитанных или записанных байт
    size_t size;
    // Массив для хранения прочитанной строки
    char   resstring[14];

    // Создаем канал от родителя к ребенку
    if(pipe(fd_p2c) < 0)
    {
        // Если создание канала не удалось, выводим сообщение об ошибке и завершаем программу
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    // Создаем канал от ребенка к родителю
    if(pipe(fd_c2p) < 0)
    {
        // Если создание канала не удалось, выводим сообщение об ошибке и завершаем программу
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    // Создаем дочерний процесс
    result = fork();

    // Если создание дочернего процесса не удалось, выводим сообщение об ошибке и завершаем программу
    if(result < 0)
    {
        printf("Can\'t fork child\n");
        exit(-1);
    }
    // Если мы находимся в родительском процессе (result > 0)
    else if (result > 0)
    {
        // Закрываем входной конец канала от родителя к ребенку, так как мы не будем читать из него
        close(fd_p2c[0]);
        // Закрываем выходной конец канала от ребенка к родителю, так как мы не будем писать в него
        close(fd_c2p[1]);

        // Записываем строку в выходной конец канала от родителя к ребенку
        size = write(fd_p2c[1], "Hello, child!", 14);

        // Если запись не удалась или было записано не все, выводим сообщение об ошибке и завершаем программу
        if(size != 14){
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        // Читаем строку из входного конца канала от ребенка к родителю
        size = read(fd_c2p[0], resstring, 14);

        // Если чтение не удалось, выводим сообщение об ошибке и завершаем программу
        if(size < 0){
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        // Закрываем выходной конец канала от родителя к ребенку, так как мы больше не будем писать в него
        close(fd_p2c[1]);
        // Закрываем входной конец канала от ребенка к родителю, так как мы больше не будем читать из него
        close(fd_c2p[0]);
        // Выводим прочитанную строку и сообщение о завершении родительского процесса
        printf("Parent exit, resstring:%s\n", resstring);

    } else {
        // Если мы находимся в дочернем процессе (result == 0)
        // Закрываем выходной конец канала от родителя к ребенку, так как мы не будем писать в него
        close(fd_p2c[1]);
        // Закрываем входной конец канала от ребенка к родителю, так как мы не будем читать из него
        close(fd_c2p[0]);

        // Читаем строку из входного конца канала от родителя к ребенку
        size = read(fd_p2c[0], resstring, 14);

        // Если чтение не удалось, выводим сообщение об ошибке и завершаем программу
        if(size < 0){
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        // Записываем строку в выходной конец канала от ребенка к родителю
        size = write(fd_c2p[1], "Hello, parent!", 14);

        // Если запись не удалась или было записано не все, выводим сообщение об ошибке и завершаем программу
        if(size != 14){
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        // Выводим прочитанную строку и сообщение о завершении дочернего процесса
        printf("Child exit, resstring:%s\n", resstring);

        // Закрываем входной конец канала от родителя к ребенку, так как мы больше не будем читать из него
        close(fd_p2c[0]);
        // Закрываем выходной конец канала от ребенка к родителю, так как мы больше не будем писать в него
        close(fd_c2p[1]);
    }

    return 0;
}