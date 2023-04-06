#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "readerwriter.h"

#define MAX_THREADS 15

void *reader(void *arg); // reader thread
void *writer(void *arg); // writer thread

int main() {
    const char *filename = "scenarios.txt";
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file!");
        exit(1);
    }

    lock_init();
    char filestring[256];
    int scenarios = 0;

    while (fgets(filestring, sizeof(filestring), file)) {
        scenarios++;
        printf("Executing scenario %d: %s\n", scenarios, filestring);

        pthread_t threads[MAX_THREADS];
        int thread_id[MAX_THREADS];
        int numthreads = 0;

        for (int i = 0; filestring[i] != '\0'; i++) {
            if (filestring[i] == 'r' || filestring[i] == 'w') {
                thread_id[numthreads] = numthreads;
                if (filestring[i] == 'r') {
                    pthread_create(&threads[numthreads], NULL, reader, &thread_id[numthreads]);
                } else {
                    pthread_create(&threads[numthreads], NULL, writer, &thread_id[numthreads]);
                }
                numthreads++;
            }
        }
        for (int i = 0; i < numthreads; i++) {
            pthread_join(threads[i], NULL);
        }
    }

    lock_destroy();
    fclose(file);
    return 0;
}

void *reader(void *arg) { 
    int id = *(int *)arg;
    printf("Create Reader\n");
    read_lock();
    printf("Reader %d is in... reading\n", id);
    reading_writing();
    printf("Reader %d finished reading\n", id);
    read_unlock();
    return NULL;
}

void *writer(void *arg) { 
    int id = *(int *)arg;
    printf("Create Writer\n");
    write_lock();
    printf("Writer %d is in... writing\n", id);
    reading_writing();
    printf("Writer %d finished writing\n", id);
    write_unlock();
    return NULL;
}

/*
Pseudocode:
while (file != NULL)
    for (i to [end of string in file])
        if (file[i] == r)
            create reader thread
        else
            create writer thread
        number of threads++
    
    for (i to number of threads)
        join threads

writer thread ()
    print("create writer")
    write_lock() <- locks mutex so no other writer can enter
    print("writer is in writing")
    reading_writing() <- acts kind of like a wait 
    print("writer finishes")
    writer_unlock() <- unlocks mutex so other writers/readers can enter

reader thread ()
    print("create reader")
    read_lock() <- locks mutex so no other reader can enter
    print("reader is in writing")
    reading_writing() <- acts kind of like a wait 
    print("reader finishes")
    read_unlock() <- unlocks mutex so other writers/readers can enter
*/