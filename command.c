//
// Created by noahmancino on 10/19/20.
//
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#define PATH_MAX 1000

void listDir() {
    char cwdStr[PATH_MAX];
    getcwd(cwdStr, sizeof(cwdStr));
    DIR *cwd = opendir(cwdStr);
    struct dirent *nextFile;

    // Loop through the files
    while ((nextFile = readdir(cwd)) != NULL) {
        // Get the file's name.
        char *fileName = nextFile->d_name;
        // Write the file's name to stdout
        write(STDOUT_FILENO, fileName, strlen(fileName));
        write(STDOUT_FILENO, "\n", 1);
    }
    closedir(cwd);
}

void showCurrentDir() {
    char cwdStr[PATH_MAX];
    getcwd(cwdStr, sizeof(cwdStr));
    write(STDOUT_FILENO, cwdStr, strlen(cwdStr));
}

void makeDir(char *dirName) {
    printf("mking");
}

void changeDir(char *dirName) {
    printf("cding");
}

void copyFile(char *sourcePath, char *destinationPath) {
    printf("cping");
}

void moveFile(char *sourcePath, char *destinationPath) {
    printf("mving");
}

void deleteFile(char *filename) {
    printf("rming");
}

void displayFile(char *filename) {
    char absPath[PATH_MAX];
    char buff[5];
    getcwd(absPath, sizeof(absPath));
    strcat(absPath, "/");
    strcat(absPath, filename);
    printf("%s", absPath);
    int fd = open(absPath, O_RDONLY);
    while (read(fd, buff, 1) != 0) {
        write(STDOUT_FILENO, buff, 1);
    }
    close(fd);
}