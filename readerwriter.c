#include "thread.h"

#define MAX_READERS 100
#define MAX_WRITERS 100
#define MAXNUM 100
#define MAX_RW 15

Thread threadarray[100];

int main (int argc, char *argv[]) {
    char filestr[MAXNUM]; // array of strings
    char filestrings[MAXNUM][MAX_RW]; // accesses individual characters of each string

    int numscenario = 0; // counts how many strings are in file
    //int filestrlen; // length of each string

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    FILE *file = fopen("scenarios.txt", "r");

    if (!file) {
        printf("Error opening file.");
        exit(1);
    }

    int readerthreadnum = 0; // keeps track how many readers
    int writerthreadnum = 0; // keeps track how many writers

    while (fgets(filestr, MAXNUM, file) != NULL) {
        int filestrlen = strlen(filestr);
        if (filestrlen > 0 && filestr[filestrlen - 1] == '\n') filestrlen--;
        for (int i = 0; i < filestrlen; i++) {
            //strcpy(&filestrings[numscenario], filestr);
            filestrings[numscenario][i] = filestr[i];

            if (filestrings[numscenario][i] == 'r') {
                readerthreadnum++;
                char* id = (char*)malloc(sizeof(char));
                *id = 'r';
                pthread_create(&readers[i], NULL, reader, (void*)id);
            } else
            if (filestrings[numscenario][i] == 'w') {
                writerthreadnum++;
                char* id = (char*)malloc(sizeof(char));
                *id = 'w';
                pthread_create(&writers[i], NULL, writer, (void*)id);
            }
        }
        numscenario++;
    }

    // for (int i = 0; i < numscenario; i++) {
    //     for (int j = 0; j < filestrlen; j++) {
    //         if (filestrings[numscenario][j] == 'r') {
    //             readerthreadnum++;
    //             char* id = (char*)malloc(sizeof(char));
    //             *id = 'r';
    //             pthread_create(&readers[readerthreadnum], NULL, reader, (void*)id);
    //         } else
    //         if (filestrings[numscenario][j] == 'w') {
    //             writerthreadnum++;
    //             char* id = (char*)malloc(sizeof(char));
    //             *id = 'w';
    //             pthread_create(&writers[writerthreadnum], NULL, writer, (void*)id);
    //         }
    //     }
    // }

    // for (int i = 0; i < numscenario; i++) {
    //     printf("%s\n", filestrings[i]);
    //     printf("%d\n", i);
    // }

    for (int i = 0; i < readerthreadnum; i++) {
        pthread_join(readers[i], NULL);
    }
    
    for (int i = 0; i < writerthreadnum; i++) {
        pthread_join(writers[i], NULL);
    }

    // joinThreads(threadarray, i);

    fclose(file);
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
// #define Thread pthread_t
// #define joinThread(thread) pthread_join(thread, NULL)

// #define MAX_READERS 100
// #define MAX_WRITERS 100
// #define MAXNUM 100
// #define MAX_RW 15

// sem_t mutex, write_mutex;
// int readers_count = 0;
// int data = 0;

// void* reader(void* arg) {
//     char* thread_id = (char*)arg;
//     while (1) {
//         // Reader waits for other readers to finish before reading
//         sem_wait(&mutex);
//         readers_count++;
//         if (readers_count == 1) {
//             // First reader acquires the write mutex to prevent writers from accessing data
//             sem_wait(&write_mutex);
//         }
//         sem_post(&mutex);

//         // Reader reads data
// 		printf("Create reader\n");
//         printf("Reader %s is reading data: %d\n", thread_id, data);
// 		printf("Finished reading\n");

//         sem_wait(&mutex);
//         readers_count--;
//         if (readers_count == 0) {
//             // Last reader releases the write mutex
//             sem_post(&write_mutex);
//         }
//         sem_post(&mutex);

//         // Reader rests
//         sleep(1);
//     }
// }

// void* writer(void* arg) {
//     char* thread_id = (char*)arg;
//     while (1) {
//         // Writer waits for the write mutex
//         sem_wait(&write_mutex);

//         // Writer modifies the data
//         data++;
// 		printf("Create writer\n");
//         printf("Writer %s is writing data: %d\n", thread_id, data);
// 		printf("Finished writing\n");

//         // Writer releases the write mutex
//         sem_post(&write_mutex);

//         // Writer rests
//         sleep(1);
//     }
// }
// Thread createThread(void* threadFunction, void* args) {
// 	Thread thread; 
// 	pthread_create(&thread, NULL, threadFunction, args);
// 	return thread;
// }

// void joinThreads(Thread* threads, int count) {
// 	int i; 
// 	for (i = 0; i < count; i++)
// 		joinThread(threads[i]);
// }

// int main (int argc, char *argv[]) {
//     char filestr[MAXNUM]; // array of strings
//     char filestrings[MAXNUM][MAX_RW]; // accesses individual characters of each string

//     int numscenario = 0; // counts how many strings are in file
//     int filestrlen; // length of each string

//     sem_init(&mutex, 0, 1);
//     sem_init(&write_mutex, 0, 1);

//     pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
//     FILE *file = fopen("scenarios.txt", "r");

//     if (!file) {
//         printf("Error opening file.");
//         exit(1);
//     }

//     int readerthreadnum = 0; // keeps track how many readers
//     int writerthreadnum = 0; // keeps track how many writers

//     char c;
//     while ((c = fgetc(file)) != EOF) {
//     if (c == 'r') {
//             readerthreadnum++;
//         } else if (c == 'w') {
//             writerthreadnum++;
//         }
//     }
//     // while (fgets(filestr, MAXNUM, file) != NULL) {
//     //     filestrlen = strlen(filestr);
//     //     if (filestrlen > 0 && filestr[filestrlen - 1] == '\n') filestrlen--;
//     //     for (int i = 0; i < filestrlen; i++) {
//     //         //strcpy(&filestrings[numscenario], filestr);
//     //         filestrings[numscenario][i] = filestr[i];

//     //         if (filestrings[numscenario][i] == 'r') {
//     //             readerthreadnum++;
//     //             char* id = (char*)malloc(sizeof(char));
//     //             *id = 'r';
//     //             pthread_create(&readers[readerthreadnum], NULL, reader, (void*)id);
//     //         } else
//     //         if (filestrings[numscenario][i] == 'w') {
//     //             writerthreadnum++;
//     //             char* id = (char*)malloc(sizeof(char));
//     //             *id = 'w';
//     //             pthread_create(&writers[writerthreadnum], NULL, writer, (void*)id);
//     //         }
//     //     }
//     //     numscenario++;
//     // }

//     for (int i = 0; i < readerthreadnum; i++) {
//     char* id = (char*)malloc(sizeof(char));
//     *id = 'r';
//     pthread_create(&readers[i], NULL, reader, (void*)id);
// }

// for (int i = 0; i < writerthreadnum; i++) {
//     char* id = (char*)malloc(sizeof(char));
//     *id = 'w';
//     pthread_create(&writers[i], NULL, writer, (void*)id);
// }

//     for (int i = 0; i < readerthreadnum; i++) {
//         pthread_join(readers[i], NULL);
//     }
    
//     for (int i = 0; i < writerthreadnum; i++) {
//         pthread_join(writers[i], NULL);
//     }

//     fclose(file);
//     sem_destroy(&mutex);
//     sem_destroy(&write_mutex);
//     return 0;
// }


// // int main (int argc, char *argv[]) {
// //     char filestr[MAXNUM]; // array of strings
// //     char filestrings[MAXNUM][MAX_RW]; // accesses individual characters of each string

// //     int numscenario = 0; // counts how many strings are in file
// //     int filestrlen; // length of each string

// //     sem_init(&mutex, 0, 1);
// //     sem_init(&write_mutex, 0, 1);

// //     pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
// //     FILE *file = fopen("scenarios.txt", "r");

// //     if (!file) {
// //         printf("Error opening file.");
// //         exit(1);
// //     }

// //     int readerthreadnum = 0; // keeps track how many readers
// //     int writerthreadnum = 0; // keeps track how many writers

// //     while (fgets(filestr, MAXNUM, file) != NULL) {
// //         filestrlen = strlen(filestr);
// //         if (filestrlen > 0 && filestr[filestrlen - 1] == '\n') filestrlen--;
// //         for (int i = 0; i < filestrlen; i++) {
// //             //strcpy(&filestrings[numscenario], filestr);
// //             filestrings[numscenario][i] = filestr[i];
// //         }
// //         numscenario++;
// //     }

// //     for (int i = 0; i < numscenario; i++) {
// //         for (int j = 0; j < filestrlen; j++) {
// //             if (filestrings[numscenario][j] == 'r') {
// //                 readerthreadnum++;
// //                 char* id = (char*)malloc(sizeof(char));
// //                 *id = 'r';
// //                 pthread_create(&readers[readerthreadnum], NULL, reader, (void*)id);
// //             } else
// //             if (filestrings[numscenario][j] == 'w') {
// //                 writerthreadnum++;
// //                 char* id = (char*)malloc(sizeof(char));
// //                 *id = 'w';
// //                 pthread_create(&writers[writerthreadnum], NULL, writer, (void*)id);
// //             }
// //         }
// //     }

// //     // for (int i = 0; i < numscenario; i++) {
// //     //     printf("%s\n", filestrings[i]);
// //     //     printf("%d\n", i);
// //     // }

// //     for (int i = 0; i < readerthreadnum; i++) {
// //         pthread_join(readers[i], NULL);
// //     }
    
// //     for (int i = 0; i < writerthreadnum; i++) {
// //         pthread_join(writers[i], NULL);
// //     }

// //     // joinThreads(threadarray, i);

// //     fclose(file);
// //     sem_destroy(&mutex);
// //     sem_destroy(&write_mutex);
// //     return 0;
// // }