#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex; // mutex
int shared_data = 0;

void* critical_section(void* arg) {
    int id = *(int*)arg;
    
    printf("Thread %d trying to enter critical section...\n", id);
    pthread_mutex_lock(&mutex); // lock
    printf("Thread %d entered critical section.\n", id);

    shared_data++;
    printf("Thread %d updated shared_data to %d\n", id, shared_data);
    sleep(1); // simulate work

    printf("Thread %d leaving critical section.\n", id);
    pthread_mutex_unlock(&mutex); // unlock
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int id1 = 1, id2 = 2, id3 = 3;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, critical_section, &id1);
    pthread_create(&t2, NULL, critical_section, &id2);
    pthread_create(&t3, NULL, critical_section, &id3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&mutex);
    printf("Final shared_data: %d\n", shared_data);
    return 0;
}

