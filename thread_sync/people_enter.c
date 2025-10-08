#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define people_count 3
sem_t door;
void *entery(void *arg){
	int id = *(int*)arg;
	printf("person %d waiting to enter into door\n", id);
	sem_wait(&door);
	printf("Person %d enterd into door\n", id);
	sleep(3);
	printf("Person %d leaving door\n", id);
	sem_post(&door);
	free(arg);
	return NULL;
}int main(){
	int i;
	pthread_t people[people_count];
	sem_init(&door, 0, 1);
	for(i = 0; i < people_count; i++){
		int *id = malloc(sizeof(int));
		*id = i+1;
		pthread_create(&people[i], NULL, entery, id);
	}for(i = 0; i < people_count; i++){
		pthread_join(people[i], NULL);
	}sem_destroy(&door);
	return 0;
}
