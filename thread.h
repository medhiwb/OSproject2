#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define Thread pthread_t
#define Semaphore sem_t
#define exitThreads() pthread_exit(NULL)
#define newInt(n) (int*)malloc(sizeof(int)*n)
#define wait(semaphore) sem_wait(&semaphore)
#define signal(semaphore) sem_post(&semaphore)
#define joinThread(thread) pthread_join(thread, NULL)
#define init(semaphore, value) sem_init(&semaphore, 0, value)

int* createArgs(int i)
{
	int* args=newInt(1); args[0]=i; return args; 
}

Thread createThread(void* threadFunction, void* args)
{
	Thread thread; pthread_create
	(
		&thread, NULL, threadFunction, args
	); 
	return thread;
}

void joinThreads(Thread* threads, int count)
{
	int i; for(i=0; i<count; i++)joinThread(threads[i]);
}