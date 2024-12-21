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
    // Идентификатор создаваемого потока
    pthread_t thid;
    // Идентификатор текущего (главного) потока
    pthread_t mythid;
    // Переменная для хранения результата создания потока
    int result;

    // Создаем новый поток
    result = pthread_create(&thid, (pthread_attr_t *)NULL, mythread, NULL);

    // Проверяем результат создания потока
    if (result != 0) {
        printf("Error on thread create, return value = %d\n", result);
        exit(-1);
    }

    // Выводим идентификатор созданного потока
    printf("Thread created, thid = %u\n", thid);

    // Получаем идентификатор текущего (главного) потока
    mythid = pthread_self();

    // Увеличиваем значение глобальной переменной в главном потоке
    a = a + 1;

    // Выводим идентификатор главного потока и результат вычисления
    printf("Thread %u, Calculation result = %d\n", mythid, a);

    // Ожидаем завершения созданного потока
    pthread_join(thid, (void **)NULL);

    return 0;
}