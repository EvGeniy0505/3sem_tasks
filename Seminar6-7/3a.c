#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    // Указатель на массив в разделяемой памяти
    int *array;
    // Идентификатор сегмента разделяемой памяти
    int shmid;
    // Флаг, указывающий, создается ли новый сегмент (1) или используется существующий (0)
    int new = 1;
    // Имя файла, используемого для генерации ключа
    char pathname[] = "03-a.c";
    // Ключ для разделяемой памяти
    key_t key;
    // Переменная для цикла задержки
    long i;

    // Генерируем ключ для разделяемой памяти
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    // Пытаемся создать новый сегмент разделяемой памяти
    if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        // Если ошибка не связана с существованием сегмента (EEXIST), завершаем программу
        if (errno != EEXIST) {
            printf("Can't create shared memory\n");
            exit(-1);
        } else {
            // Если сегмент уже существует, получаем доступ к нему
            if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
                printf("Can't find shared memory\n");
                exit(-1);
            }
            // Устанавливаем флаг, что используется существующий сегмент
            new = 0;
        }
    }

    // Присоединяем сегмент разделяемой памяти к адресному пространству процесса
    if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    // Если сегмент новый, инициализируем массив
    if (new) {
        array[0] = 1;  // Количество запусков программы 1
        array[1] = 0;  // Количество запусков программы 2
        array[2] = 1;  // Общее количество запусков
    } else {
        // Если сегмент существует, обновляем значения
        array[0] += 1;  // Увеличиваем счетчик запусков программы 1
        // Задержка для имитации длительной работы
        for (i = 0; i < 2000000000L; i++);
        array[2] += 1;  // Увеличиваем общий счетчик запусков
    }

    // Выводим статистику запусков программ
    printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
           array[0], array[1], array[2]);

    // Отсоединяем сегмент разделяемой памяти
    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}