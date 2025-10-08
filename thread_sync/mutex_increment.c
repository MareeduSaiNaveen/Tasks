#include<stdio.h>
#include<pthread.h>
#define thread_count 5
#define MAX 100000
int num_g = 0;
pthread_mutex_t lock;
void *increment(void *arg){
	int i;
	for(i = 0; i < MAX; i++){
		pthread_mutex_lock(&lock);
		num_g++;
		pthread_mutex_unlock(&lock);
	}pthread_exit(NULL);
}int main(){
	int i;
	pthread_t ti[thread_count];
	pthread_mutex_init(&lock, NULL);
	for(i = 0; i < thread_count; i++){
		pthread_create(&ti[i], NULL, increment, NULL);
	}for(i = 0; i < thread_count; i++){
		pthread_join(ti[i], NULL);
	}pthread_mutex_destroy(&lock);
	printf("After increment by %d threads : %d\n", thread_count, num_g);
	return 0;
}
