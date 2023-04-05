#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define Thread pthread_t
#define joinThread(thread) pthread_join(thread, NULL)

sem_t mutex, write_mutex;
int readers_count = 0;
int data = 0;

void* reader(void* arg) {
    char* thread_id = (char*)arg;
    while (1) {
        // Reader waits for other readers to finish before reading
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            // First reader acquires the write mutex to prevent writers from accessing data
            sem_wait(&write_mutex);
        }
        sem_post(&mutex);

        // Reader reads data
		printf("Create reader\n");
        printf("Reader %s is reading data: %d\n", thread_id, data);
		printf("Finished reading\n");

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            // Last reader releases the write mutex
            sem_post(&write_mutex);
        }
        sem_post(&mutex);

        // Reader rests
        sleep(1);
    }
}

void* writer(void* arg) {
    char* thread_id = (char*)arg;
    while (1) {
        // Writer waits for the write mutex
        sem_wait(&write_mutex);

        // Writer modifies the data
        data++;
		printf("Create writer\n");
        printf("Writer %s is writing data: %d\n", thread_id, data);
		printf("Finished writing\n");

        // Writer releases the write mutex
        sem_post(&write_mutex);

        // Writer rests
        sleep(1);
    }
}
Thread createThread(void* threadFunction, void* args) {
	Thread thread; 
	pthread_create(&thread, NULL, threadFunction, args);
	return thread;
}

void joinThreads(Thread* threads, int count) {
	int i; 
	for (i = 0; i < count; i++)
		joinThread(threads[i]);
}