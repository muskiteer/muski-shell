#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc <2 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: echo [STRING...]\n");
        printf("Print the STRING to standard output.\n");
        return 0;
    }
    for(int i=1;i<argc;i++){
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}