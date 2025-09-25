#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 100

// Mailbox structure
typedef struct {
    char message[MSG_SIZE];
    int full; // 0 = empty, 1 = full
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Mailbox;

Mailbox mbox;

// Sender thread
void* sender(void* arg) {
    char* msg = (char*)arg;
    pthread_mutex_lock(&mbox.lock);
    
    while(mbox.full) {
        pthread_cond_wait(&mbox.cond, &mbox.lock); // Wait if mailbox full
    }
    
    strcpy(mbox.message, msg);
    mbox.full = 1;
    printf("Message sent: %s\n", msg);
    
    pthread_cond_signal(&mbox.cond); // Notify receiver
    pthread_mutex_unlock(&mbox.lock);
    
    return NULL;
}

// Receiver thread
void* receiver(void* arg) {
    pthread_mutex_lock(&mbox.lock);
    
    while(!mbox.full) {
        pthread_cond_wait(&mbox.cond, &mbox.lock); // Wait if mailbox empty
    }
    
    printf("Message received: %s\n", mbox.message);
    mbox.full = 0;
    
    pthread_cond_signal(&mbox.cond); // Notify sender
    pthread_mutex_unlock(&mbox.lock);
    
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mbox.lock, NULL);
    pthread_cond_init(&mbox.cond, NULL);
    mbox.full = 0;

    pthread_create(&t1, NULL, sender, "Hello from Mailbox!");
    sleep(1); // Ensure sender runs first
    pthread_create(&t2, NULL, receiver, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mbox.lock);
    pthread_cond_destroy(&mbox.cond);
    
    return 0;
}

