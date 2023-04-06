#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "readerwriter.h"

sem_t resource_lock, rw_mutex, writer_mutex, reader_mutex;
int read_count = 0;
int write_count = 0;

void read_lock() {
    sem_wait(&reader_mutex);
    sem_wait(&writer_mutex); 
    sem_wait(&rw_mutex);
    read_count++;
    if (read_count == 1)
    {
        sem_wait(&resource_lock);
    }
    sem_post(&rw_mutex);
    sem_post(&writer_mutex); 
    sem_post(&reader_mutex); 
}

void read_unlock() {
    sem_wait(&rw_mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource_lock);
    }
    sem_post(&rw_mutex);
}

void write_lock() {
    sem_wait(&writer_mutex); 
    write_count++;     
    if (write_count == 1) {
        sem_wait(&reader_mutex);
    }
    sem_post(&writer_mutex); 
    sem_wait(&resource_lock);
}

void write_unlock() {
    sem_post(&resource_lock);
    sem_wait(&writer_mutex); 
    write_count--;           
    if (write_count == 0) {
        sem_post(&reader_mutex);
    }
    sem_post(&writer_mutex); 
}

void lock_init() {
    sem_init(&resource_lock, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    sem_init(&writer_mutex, 0, 1); 
    sem_init(&reader_mutex, 0, 1);
}

void lock_destroy() {
    sem_destroy(&resource_lock);
    sem_destroy(&rw_mutex);
    sem_destroy(&writer_mutex); 
    sem_destroy(&reader_mutex); 
}

void reading_writing() {
    int x = 0, j = 0, i = 0;
    int T = rand() % 10000;
    for (i = 0; i < T; i++) {
        for (j = 0; j < T; j++) {
            x = i * j;
        }
    }
}