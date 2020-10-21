#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

/*
 * Simply makes sure the arg string isn't NULL or a semicolon.
 */
int valid_single_arg(char *arg) {
    return !(arg == NULL || arg[0] == ';');
}
/*
 * Checks that neither arg strings are NULL or a semicolon.
 */
int valid_double_arg(char *arg1, char* arg2) {
    return !(arg1 == NULL || arg1[0] == ';' || arg2 == NULL || arg2[0] == ';');
}

int main(int argc, char *argv[]) {
    // Everything is written to stdout. You can specify where stout should go with the -f flag and a filename.
    if (argc > 1) {
        if (strcmp("-f", argv[1]) == 0) {
            freopen(argv[2], "w", stdout);
        }
        else {
            printf("Incorrect usage!");
            exit(EXIT_FAILURE);
        }
    }

    size_t size = 0;
    char *input = NULL;
    // repl
    while (1) {
        printf(">>> ");
        getline(&input, &size, stdin);
        char *token = strtok(input, " \n");
        int final_semi = 0;
        int all_args = 0;
        do {
            printf("%d", all_args);
            if (strcmp(";", token) == 0) {
                final_semi = 1;
                all_args = 0;
                continue;
            }
            if (all_args) {
                printf("ERROR HERE1");
                break;
            }
            if (strcmp("exit", token) == 0) {
                free(input);
                fclose(stdout);
                exit(EXIT_SUCCESS);
            } else if (strcmp("ls", token) == 0) {
                listDir();
                printf("");
                all_args = 1;
            } else if (strcmp("pwd", token) == 0) {
                showCurrentDir();
                printf("\n");
                all_args = 1;
            } else if (strcmp("mkdir", token) == 0) {
                char *arg = strtok(NULL, " \n");
                if (valid_single_arg(arg)) {
                    makeDir(arg);
                    printf("");
                    all_args = 1;
                }
                else {
                    //TODO: Print
                    break;
                }
            } else if (strcmp("cp", token) == 0) {
                char *arg = strtok(NULL, " \n");
                char *arg2 = strtok(NULL, " \n");
                if (valid_double_arg(arg, arg2)) {
                    copyFile(arg, arg2);
                    printf("");
                    all_args = 1;
                }
                else {
                    //TODO: Print
                    break;
                }
            } else if (strcmp("cd", token) == 0) {
                char *arg = strtok(NULL, " \n");
                if (valid_single_arg(arg)) {
                    changeDir(arg);
                    printf("");
                    all_args = 1;
                }
                else {
                    //TODO: Print
                    break;
                }
            } else if (strcmp("mv", token) == 0) {
                char *arg = strtok(NULL, " \n");
                char *arg2 = strtok(NULL, " \n");
                if (valid_double_arg(arg, arg2)) {
                    moveFile(arg, arg2);
                    printf("");
                    all_args = 1;
                }
                else {
                    //TODO: Print
                    break;
                }
            } else if (strcmp("rm", token) == 0) {
                char *arg = strtok(NULL, " \n");
                if (valid_single_arg(arg)) {
                    deleteFile(arg);
                    printf("");
                    all_args = 1;
                }
                else {
                    //TODO: Print
                    break;
                }
            } else if (strcmp("cat", token) == 0) {
                char *arg = strtok(NULL, " \n");
                if (valid_single_arg(arg)) {
                    displayFile(arg);
                    printf("");
                    all_args = 1;
                }
                else {
                    //TODO: Print
                    break;
                }
            } else {
                printf("Error: unrecognized command %s", input);
                break;
            }
        }
        while ((token = strtok(NULL, " \n")) != NULL);
        if (final_semi) {
            printf("ERROR HERE2");
        }
    }
}
