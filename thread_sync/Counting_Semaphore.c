#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CONCURRENT 2

sem_t count_sem; // counting semaphore
int shared_data = 0;

void* critical_section(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d waiting to enter critical section...\n", id);
    sem_wait(&count_sem); // acquire
    printf("Thread %d entered critical section.\n", id);

    shared_data++;
    printf("Thread %d updated shared_data to %d\n", id, shared_data);
    sleep(1); // simulate work

    printf("Thread %d leaving critical section.\n", id);
    sem_post(&count_sem); // release
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4, t5;
    int id1=1, id2=2, id3=3, id4=4, id5=5;

    sem_init(&count_sem, 0, MAX_CONCURRENT); // initialize counting semaphore

    pthread_create(&t1, NULL, critical_section, &id1);
    pthread_create(&t2, NULL, critical_section, &id2);
    pthread_create(&t3, NULL, critical_section, &id3);
    pthread_create(&t4, NULL, critical_section, &id4);
    pthread_create(&t5, NULL, critical_section, &id5);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    sem_destroy(&count_sem);
    printf("Final shared_data: %d\n", shared_data);
    return 0;
}

