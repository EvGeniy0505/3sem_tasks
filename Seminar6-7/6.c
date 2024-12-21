#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Глобальная переменная, используемая для демонстрации совместного доступа
int a = 0;

// Функция потока
void *mythread(void *dummy)
/*
 *   Параметр void *dummy используется только для совместимости типов и не будет использоваться
 *   в функции. По той же причине возвращаемое значение функции имеет тип void *, но оно
 *   не будет использоваться в этой программе.
 */
{
    // Получаем идентификатор текущего потока
    pthread_t mythid;
    mythid = pthread_self();

    // Увеличиваем значение глобальной переменной
    a = a + 1;

    // Выводим идентификатор потока и результат вычисления
    printf("Thread %u, Calculation result = %d\n", mythid, a);

    return NULL;
}

int main()
{
    // Идентификаторы создаваемых потоков
    pthread_t thid1, thid2;
    // Идентификатор текущего (главного) потока
    pthread_t mythid;
    // Переменные для хранения результатов создания потоков
    int result1, result2;

    // Создаем первый поток
    result1 = pthread_create(&thid1, (pthread_attr_t *)NULL, mythread, NULL);
    // Создаем второй поток
    result2 = pthread_create(&thid2, (pthread_attr_t *)NULL, mythread, NULL);

    // Проверяем результаты создания потоков
    if (result1 != 0 || result2 != 0) {
        printf("Error on thread create, return values = %d; %d\n", result1, result2);
        exit(-1);
    }

    // Выводим идентификаторы созданных потоков
    printf("Thread1 created, thid = %u\n", thid1);
    printf("Thread2 created, thid = %u\n", thid2);

    // Получаем идентификатор текущего (главного) потока
    mythid = pthread_self();

    // Увеличиваем значение глобальной переменной в главном потоке
    a = a + 1;

    // Выводим идентификатор главного потока и результат вычисления
    printf("Thread %u, Calculation result = %d\n", mythid, a);

    // Ожидаем завершения первого потока
    pthread_join(thid1, (void **)NULL);
    // Ожидаем завершения второго потока
    pthread_join(thid2, (void **)NULL);

    return 0;
}