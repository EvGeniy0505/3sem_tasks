#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>

int main() {
    // Указатель на буфер, который будет использоваться для хранения содержимого файла в разделяемой памяти
    char* buf = NULL;
    // Идентификатор разделяемой памяти
    int shmid = 0;
    // Имя файла, который будет читаться
    const char* filename = "02-a.c";
    // Ключ для разделяемой памяти
    key_t key = 0;

    // Открываем файл в режиме чтения бинарных данных
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Can't open file");
        return -1;
    }

    // Определяем размер файла
    fseek(file, 0, SEEK_END);  // Перемещаем указатель в конец файла
    long file_size = ftell(file) + 1;  // Получаем размер файла и добавляем 1 для нуль-терминатора
    fseek(file, 0, SEEK_SET);  // Возвращаем указатель в начало файла

    // Генерируем ключ для разделяемой памяти с использованием файла и идентификатора 0
    if ((key = ftok(filename, 0)) < 0) {
        fprintf(stderr, "Can't generate key\n");
        return -2;
    }

    // Создаем новый сегмент разделяемой памяти
    // Размер сегмента: file_size * sizeof(char), права доступа: 0666 (чтение и запись для всех),
    // флаги: IPC_CREAT (создать, если не существует) и IPC_EXCL (ошибка, если уже существует)
    if ((shmid = shmget(key, file_size * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        perror("shmget err");
        return -3;
    }

    // Присоединяем сегмент разделяемой памяти к адресному пространству процесса
    if ((buf = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)) {
        fprintf(stderr, "Can't attach shared memory\n");
        return -4;
    }

    // Читаем содержимое файла в буфер разделяемой памяти
    fread(buf, file_size, sizeof(char), file);

    // Закрываем файл
    fclose(file);

    // Отсоединяем сегмент разделяемой памяти от адресного пространства процесса
    if (shmdt(buf) < 0) {
        printf("Can't detach shared memory\n");
        return -5;
    }

    return 0;
}