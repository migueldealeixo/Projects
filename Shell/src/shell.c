#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64


void execute_builtin(char **args);
void handle_command(char **args);
int parse_input(char *input, char **args);
void execute_external_command(char **args);


void run_shell() {
    char command[MAX_CMD_LENGTH];
    char *args[MAX_ARGS];

    while (1) {

        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s> ", cwd);
        } else {
            printf("myshell> ");
        }


        if (!fgets(command, sizeof(command), stdin)) {
            break;  
        }


        command[strcspn(command, "\n")] = 0;

     
        int arg_count = parse_input(command, args);
        if (arg_count == 0) {
            continue;  
        }


        if (strcmp(args[0], "exit") == 0) {
            break;  
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
            continue;  
        } else if (strcmp(args[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd");
            }
            continue;  
        } else if (strcmp(args[0], "help") == 0) {
            printf("Built-in commands:\n");
            printf("  exit  - Exit the shell\n");
            printf("  cd <directory> - Change directory\n");
            printf("  pwd - Print current working directory\n");
            printf("  help - Show this message\n");
            continue;
        }

       
        execute_external_command(args);
    }
}


int parse_input(char *input, char **args) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return i;
}


void execute_external_command(char **args) {
    int background = 0;
    int i = 0;
    
  
    while (args[i] != NULL) {
        if (strcmp(args[i], "&") == 0) {
            background = 1;
            args[i] = NULL; 
            break;
        }
        i++;
    }

    pid_t pid = fork();
    if (pid == 0) {
        
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(1);
    } else if (pid < 0) {
        perror("fork");
    } else {
      
        if (!background) {
            wait(NULL);  
        }
    }
}
