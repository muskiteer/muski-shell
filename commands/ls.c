#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>


int main(int args,char *argv[]){

    if (args > 2 || (args == 2 && strcmp(argv[1], "--help") == 0)) {
        printf("Usage: ls [DIRECTORY]\n");
        printf("List files in the specified DIRECTORY or current directory.\n");
        return 0;
    }
    
    const char *dir;
    dir = args == 2 ? argv[1]:".";

   
    DIR *d = opendir(dir);
    if (!d){
        perror("opendir");
        return 1;
    }
    struct dirent *entry;

    while ((entry = readdir(d)) != NULL) {
        int is_dir = 0;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        struct stat st;
        if(entry->d_type!=DT_UNKNOWN){
            // If d_type is known, we can use it directly
            // it is pretty useful
            is_dir = (entry->d_type == DT_DIR);
        }
        else if (stat(path, &st) == 0) {
            is_dir = S_ISDIR(st.st_mode);
        }

        if (is_dir) {
            printf("\033[0;34m%s\033[0m     ", entry->d_name);
        } else {
            printf("\033[0;32m%s\033[0m     ", entry->d_name);
        }
    }
    printf("\n");
    
    closedir(d);

    return 0;
}

