#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define avd_slot 3
#define car_count 5
sem_t slot;
void *parking(void *arg){
	char* car_id = (char*)arg;
	printf("%s's car waiting to enter into parking\n", car_id);
	sem_wait(&slot);
	printf("%s's car is enterd into parking\n", car_id);
	sleep(3);
	printf("%s's car is leaving from parking\n", car_id);
	sem_post(&slot);
	return NULL;
}int main(){
	int i;
	pthread_t cars[car_count];
	char *arr[] = {"sai", "venkata", "raghu", "gopal", "ajay"};
	sem_init(&slot, 0, avd_slot);
	for(i = 0; i < car_count; i++){
		pthread_create(&cars[i], NULL, parking, arr[i]);
	}for(i = 0; i < car_count; i++){
		pthread_join(cars[i], NULL);
	}sem_destroy(&slot);
	return 0;
}
