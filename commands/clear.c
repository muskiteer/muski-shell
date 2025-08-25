#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("just clear the shit\n");
        return 0;   
    }
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("bro doesn’t even know how to use clear\n");
        printf("just clear the shit\n");
        return 0;
    }
    if (argc == 2) {
        printf("just clear the shit\n");
        return 0;
    }

    printf("\033[H\033[2J\033[3J");
    fflush(stdout);

     return 0;
}



