#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

#define MAX_LINE 1024
#define MAX_PATH 256
#define MAX_ARGS 100

int command_cd(int argc,char *argv[MAX_ARGS]) {
    const char *dir;

    if (argc > 2){
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }
    if (argv[1] == NULL || strcmp(argv[1], "~") == 0) {
        struct passwd *pw = getpwuid(getuid());
        if (pw == NULL){
            perror("cd: getpwuid failed");
            return 1;
        }
        dir = pw->pw_dir ? pw->pw_dir : "/";
    }else{
        dir = argv[1];
    }

    if (chdir(dir) != 0) {
            perror("cd: ");
            return 1;
    }
    return 0;
}



int main(){
    char line[MAX_LINE];
    char *myargs[MAX_ARGS];
    char cwd[MAX_PATH];
  
   
    while(1){
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd failed");
            continue;
        }

        printf("Muski-shell: %s>\n", cwd);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            perror("fgets failed");
            continue;   
        }
        if (line[0] == '\n') {
            continue; 
        }
        line[strcspn(line, "\n")] = '\0'; 
        if (strcmp(line, "exit")==0){
            break;
        }
        
        
        char *token = strtok(line, " ");
        int i = 0;
        while(token != NULL && i < MAX_ARGS - 1) {
            myargs[i++] = token;
            token = strtok(NULL, " ");
        }
        myargs[i] = NULL;

        if (strcmp(myargs[0], "exit") == 0){
            exit(0);
        }

        
        
        char path[256];
        snprintf(path, sizeof(path), "./build/%s", myargs[0]);

        if (strcmp(myargs[0],"cd")==0){
            command_cd(i, myargs);
            continue;
        }

        int pid = fork();

        if (pid <0){
            perror("Fork failed\n");
            continue;
        }
        if (pid == 0){
            if (execv(path, myargs) < 0) {
                fprintf(stderr, "Command not found: %s\n", myargs[0]);
                printf("hello");
            }
            exit(EXIT_FAILURE);
        }
        else {
            wait(NULL);
            continue;
        }        
    }
        return 0;
}