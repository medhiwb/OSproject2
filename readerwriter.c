#include "thread.h"

int main () {
    char rw;
    FILE *file = fopen("scenarios.txt", "r");

    if (!file) {
        printf("Error opening file.");
        exit(1);
    }

    while(fscanf(file, "%c", &rw) != EOF) {
        int i;
        if (rw == 'r') {

        } else {
            
        }
        
    }
}