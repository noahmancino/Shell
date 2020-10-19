#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

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
    char *token = (char *)malloc(sizeof(char) * PATH_MAX)
    // repl
    while (1) {
        printf(">>> ");
        getline(&input, &size, stdin);

        if (strcmp("exit\n", input) == 0) {
            free(input);
            fclose(stdout);
            exit(EXIT_SUCCESS);
        }
        else if (strcmp("ls\n", input) == 0) {
            listDir();
            printf("");
        }
        else if (strcmp("pwd\n", input) == 0) {
            showCurrentDir();
            printf("\n");
        }
        else if (strcmp("mkdir\n", input) == 0) {
            makeDir("apples");
            printf("");
        }
        else if (strcmp("cp\n", input) == 0) {
            copyFile("apples", "oranges");
        }
        else if (strcmp("cd\n", input) == 0) {
            changeDir("..");
            printf("");
        }
        else if (strcmp("mv\n", input) == 0) {
            moveFile("something.txt", "different.txt");
        }
        else if (strcmp("rm\n", input) == 0) {
            deleteFile("apples");
        }
        else if (strcmp("cat\n", input) == 0) {
            displayFile("example.txt");
            printf("");
        }
        else {
            printf("Error: unrecognized command %s", input);
        }
    }
}
