#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>

int main() {
    // Указатель на буфер, который будет использоваться для чтения содержимого разделяемой памяти
    char* buf = NULL;
    // Идентификатор разделяемой памяти
    int shmid = 0;
    // Имя файла, используемого для генерации ключа
    const char* filename = "02-a.c";
    // Ключ для разделяемой памяти
    key_t key = 0;

    // Генерируем ключ для разделяемой памяти с использованием файла и идентификатора 0
    if ((key = ftok(filename, 0)) < 0) {
        fprintf(stderr, "Can't generate key\n");
        return -1;
    }

    // Пытаемся получить идентификатор существующего сегмента разделяемой памяти
    // Размер сегмента указан как 0, так как мы только ищем существующий сегмент
    if ((shmid = shmget(key, 0, 0)) < 0) {
        perror("Can't find shared memory");
        return -2;
    }

    // Структура для хранения информации о сегменте разделяемой памяти
    struct shmid_ds ds = {};
    // Получаем информацию о сегменте разделяемой памяти
    if (shmctl(shmid, IPC_STAT, &ds) < 0) {
        perror("Can't get shared memory stat");
        return -3;
    }
    // Определяем размер сегмента разделяемой памяти (в байтах) и преобразуем его в количество символов
    int file_size = (int) ds.shm_segsz / sizeof(char);

    // Повторно получаем идентификатор сегмента разделяемой памяти с известным размером
    if ((shmid = shmget(key, file_size * sizeof(char), 0)) < 0) {
        perror("shmget err");
        return -4;
    }

    // Присоединяем сегмент разделяемой памяти к адресному пространству процесса
    if ((buf = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)) {
        fprintf(stderr, "Can't attach shared memory\n");
        return -5;
    }

    // Выводим содержимое буфера (содержимое разделяемой памяти) на стандартный вывод
    printf("%s", buf);

    // Отсоединяем сегмент разделяемой памяти от адресного пространства процесса
    if (shmdt(buf) < 0) {
        printf("Can't detach shared memory\n");
        return -6;
    }

    // Удаляем сегмент разделяемой памяти
    if (shmctl(shmid, IPC_RMID, &ds) < 0) {
        perror("Can't delete shared memory\n");
        return -7;
    }

    return 0;
}