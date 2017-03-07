#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TRUE 1
typedef int buffer_item;
#define BUFFER_SIZE 8

buffer_item START_NUMBER;
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

int insert_item(buffer_item item);
int remove_item(buffer_item *item);

void *producer(void *param);
void *consumer(void *param);

// Implementation of the insert_itme() function
int insert_item(buffer_item item)
{
	buffer[insertPointer] = item;
	insertPointer = (insertPointer + 1) % BUFFER_SIZE;
	return 0;
}

// Implementation of the remove_item() function
int remove_item(buffer_item *item)
{
	*item = buffer[removePointer];
	removePointer = (removePointer + 1) % BUFFER_SIZE;
	return 0;
}

// Implementation of the producer thread -- referred to figure 5.26 
void *producer(void *param)
{
	buffer_item item;

	while(TRUE) {
		sleep(2);
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		item = START_NUMBER++;
		insert_item(item);

		printf("Producer %u produced %d \n", (unsigned int)pthread_self(), item);

		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

// Implementation of the consumer thread -- referred to figure 5.26 
void *consumer(void *param)
{
	buffer_item item;

	while(TRUE){
		sleep(2);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);

		remove_item(&item);
		printf("Consumer %u consumed %d \n", (unsigned int)pthread_self(), item);

		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if(argc != 5)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads> <start number>\n");
		return -1;
	}

	// Set up arguments 
	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);
	START_NUMBER = atoi(argv[4]);
	
	// Initialize thr synchronization tools 
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, BUFFER_SIZE);
	sem_init(&empty, 0, 0);

	// Create producer and conusmer threads 
	// Used for loops to initiate multiple threads 
	pthread_t pid, cid;

	for(i = 0; i < producerThreads; i++){
		pthread_create(&pid,NULL,&producer,NULL);
	}

	for(j = 0; j < consumerThreads; j++){
		pthread_create(&cid,NULL,&consumer,NULL);
	}

	sleep(sleepTime);

	return 0;
}
