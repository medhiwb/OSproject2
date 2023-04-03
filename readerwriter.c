#include "thread.h"

sem_t mutex;
sem_t homeboy;

int main (int argc, char *argv[]) {
    char rw;
    // sem_init(&mutex, 0, 1);
    // sem_init(&homeboy, 0, 1);
    FILE *file = fopen("scenarios.txt", "r");

    if (!file) {
        printf("Error opening file.");
        exit(1);
    }

    // while(fscanf(file, "%c", &rw) != EOF) {
    //     int i;
    //     if (rw == 'r') {

    //     } else {
            
    //     }
        
    // }
    // sem_destroy(mutex);
    // sem_destroy(homeboy);
    int i = 0;
    while(fscanf(file, "%c", &rw) != EOF) {
        while (rw == 'r') {
            i++;
        }
        
    }
    fclose(file);
    printf("%d\n", i);
    printf("hel\n");
    return 0;
}