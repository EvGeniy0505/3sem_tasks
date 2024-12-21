#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 30


unsigned long long get_pipe_size() {
    FILE *fp;
    unsigned long long pipe_size;

    // Открываем команду "getconf PIPE_BUF /" для чтения
    fp = popen("getconf PIPE_BUF /", "r");
    if (fp == NULL) {
        // Если открытие команды не удалось, выводим сообщение об ошибке и завершаем программу
        perror("Failed to run command");
        exit(1);
    }

    // Читаем размер pipe из команды
    if (fscanf(fp, "%llu", &pipe_size) != 1) {
        // Если чтение не удалось, выводим сообщение об ошибке и завершаем программу
        perror("Failed to read pipe size");
        pclose(fp);
        exit(1);
    }

    // Закрываем команду
    pclose(fp);
    // Возвращаем размер pipe
    return pipe_size;
}

int main() {
    unsigned long long pipe_size = get_pipe_size();
    printf("Размер pipe: %llu байт\n", pipe_size);

    return 0;
}