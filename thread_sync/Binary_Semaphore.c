#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t bin_sem; // binary semaphore
int shared_data = 0;

void* critical_section(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d trying to enter critical section...\n", id);
    sem_wait(&bin_sem); // acquire
    printf("Thread %d entered critical section.\n", id);

    shared_data++;
    printf("Thread %d updated shared_data to %d\n", id, shared_data);
    sleep(1); // simulate work

    printf("Thread %d leaving critical section.\n", id);
    sem_post(&bin_sem); // release
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int id1=1, id2=2, id3=3;

    sem_init(&bin_sem, 0, 1); // initialize binary semaphore

    pthread_create(&t1, NULL, critical_section, &id1);
    pthread_create(&t2, NULL, critical_section, &id2);
    pthread_create(&t3, NULL, critical_section, &id3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&bin_sem);
    printf("Final shared_data: %d\n", shared_data);
    return 0;
}

