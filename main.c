#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

const char *NotEnoughArgs = "ERROR: not enough arguments.\n";
const char *TooManyArgs = "ERROR: too many arguments.\n";
const char *EndOnCol = "ERROR: Ending line on a semicolon.\n";
/*
 * Simply makes sure the arg string isn't NULL or a semicolon.
 */
int valid_single_arg(const char *arg) {
    return !(arg == NULL || arg[0] == ';');
}
/*
 * Checks that neither arg strings are NULL or a semicolon.
 */
int valid_double_arg(const char *arg1, const char* arg2) {
    return !(arg1 == NULL || arg1[0] == ';' || arg2 == NULL || arg2[0] == ';');
}
// TODO: Factor out the logic that's copied in each lf (make two functions that take args and a function pointer,
//  one for one arg one for two args.)

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
     // The way 'token' is used doesn't really make sense. It's really just there to prove I know what malloc does.

    char *token = (char*)malloc(sizeof(char) * 4000);
    // repl
    while (1) {
        printf(">>> ");
        getline(&input, &size, stdin);
        char *token_buf = strtok(input, " \n");
        int final_semi = 0;
        int all_args = 0;
        // Outer if is for empty lines.
        if (token_buf != NULL) {
            do {
                strcpy(token, token_buf);
                if (strcmp(";", token) == 0) {
                    final_semi = 1;
                    all_args = 0;
                    continue;
                }
                final_semi = 0;
                if (all_args) {
                    printf(TooManyArgs);
                    break;
                }
                if (strcmp("exit", token) == 0) {
                    free(token);
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
                    } else {
                        printf(NotEnoughArgs);
                        break;
                    }
                } else if (strcmp("cp", token) == 0) {
                    char *arg = strtok(NULL, " \n");
                    char *arg2 = strtok(NULL, " \n");
                    if (valid_double_arg(arg, arg2)) {
                        copyFile(arg, arg2);
                        printf("");
                        all_args = 1;
                    } else {
                        printf(NotEnoughArgs);
                        break;
                    }
                } else if (strcmp("cd", token) == 0) {
                    char *arg = strtok(NULL, " \n");
                    if (valid_single_arg(arg)) {
                        changeDir(arg);
                        printf("");
                        all_args = 1;
                    } else {
                        printf(NotEnoughArgs);
                        break;
                    }
                } else if (strcmp("mv", token) == 0) {
                    char *arg = strtok(NULL, " \n");
                    char *arg2 = strtok(NULL, " \n");
                    if (valid_double_arg(arg, arg2)) {
                        moveFile(arg, arg2);
                        printf("");
                        all_args = 1;
                    } else {
                        printf(NotEnoughArgs);
                        break;
                    }
                } else if (strcmp("rm", token) == 0) {
                    char *arg = strtok(NULL, " \n");
                    if (valid_single_arg(arg)) {
                        deleteFile(arg);
                        printf("");
                        all_args = 1;
                    } else {
                        printf(NotEnoughArgs);
                        break;
                    }
                } else if (strcmp("cat", token) == 0) {
                    char *arg = strtok(NULL, " \n");
                    if (valid_single_arg(arg)) {
                        displayFile(arg);
                        printf("");
                        all_args = 1;
                    } else {
                        printf(NotEnoughArgs);
                        break;
                    }
                } else {
                    printf("Error: unrecognized command %s\n", input);
                    break;
                }
            } while ((token_buf = strtok(NULL, " \n")) != NULL);
            if (final_semi) {
                printf(EndOnCol);
            }
        }
    }
}
