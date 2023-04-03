#include "thread.h"

sem_t mutex;
sem_t homeboy;

int main (int argc, char *argv[]) {
    char rw;
    sem_init(&mutex, 0, 1);
    sem_init(&homeboy, 0, 1);
    FILE *file = fopen("scenarios.txt", "r");

    if (!file) {
        printf("Error opening file.");
        exit(1);
    }

    int readcount = 0;
    while(fscanf(file, "%c", &rw) != EOF) {
        while (rw == 'w') {
            wait(homeboy);
            printf("Create writer");
            printf("Writer is in ... writing");;
            printf("Finished writing");
            signal(homeboy);
        }
        
        while (rw == 'r')
        {
            wait(homeboy);
            readcount++;
            
            if (readcount == 1) {
                wait(homeboy);
                signal(mutex);
            }

            printf("Create reader");
            printf("Reader is in ... reading");;
            printf("Finished reading");
            wait(homeboy);
            readcount--;

            if (readcount == 0) {
                signal(homeboy);
                signal(mutex);
            }
        }
    }
    fclose(file);
    sem_destroy(&mutex);
    sem_destroy(&homeboy);
    return 0;
}