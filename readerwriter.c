#include "thread.h"

#define MAX_READERS 100
#define MAX_WRITERS 100

int main (int argc, char *argv[]) {
    char rw;
    Thread threadarray[100];
    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    //pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    FILE *file = fopen("scenarios.txt", "r");

    if (!file) {
        printf("Error opening file.");
        exit(1);
    }

    int readcount = 0, i = 0;
    while(fscanf(file, "%c", &rw) != EOF) {
        if (rw == 'w') {
            char* id = (char*)malloc(sizeof(char));
            *id = 'w';
            // pthread_create(&readers[i], NULL, reader, (void*)id);
            threadarray[i++] = createThread(writer, id);
        } else if (rw == 'r') {
            char* id = (char*)malloc(sizeof(char));
            *id = 'r';
            // pthread_create(&writers[j], NULL, writer, (void*)id);
            threadarray[i++] = createThread(reader, id);
        }
    }

    // for (int x = 0; x < i; x++) {
    //     pthread_join(readers[x], NULL);
    // }
    
    // for (int y = 0; y < j; y++) {
    //     pthread_join(writers[y], NULL);
    // }

    joinThreads(threadarray, i);

    fclose(file);
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    return 0;
}