//
// Created by noahmancino on 10/19/20.
//
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

/*
 * ls except it doesn't ignore dot files.
 */
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

/*
 * pwd
 */
void showCurrentDir() {
    char cwdStr[PATH_MAX];
    getcwd(cwdStr, sizeof(cwdStr));
    write(STDOUT_FILENO, cwdStr, strlen(cwdStr));
}

/*
 * Makes a new directory called dirName under the current directory.
 */
void makeDir(char *dirName) {
    char dirPath[PATH_MAX];

    getcwd(dirPath, sizeof(dirPath));
    strcat(dirPath, "/");
    strcat(dirPath, dirName);

    // All permissions that don't conflict with umask will always be granted.
    if (mkdir(dirPath, 0777) == -1) {
        write(STDOUT_FILENO, "ERROR: File already exists.", 20);
    }
}

/*
 * Should always function like cd in bash.
 */
void changeDir(char *dirName) {
    char dirPath[PATH_MAX];

    getcwd(dirPath, sizeof(dirPath));
    strcat(dirPath, "/");
    strcat(dirPath, dirName);

    chdir(dirPath);
}

/*
 * Copies the source file to the destination file. Creates the destination file if it does not exist.
 */
void copyFile(char *sourcePath, char *destinationPath) {
    char absSource[PATH_MAX];
    char absDest[PATH_MAX];

    getcwd(absDest, sizeof(absDest));
    strcat(absDest, "/");
    strcpy(absSource, absDest);
    strcat(absSource, sourcePath);
    strcat(absDest, destinationPath);

    int fdSrc = open(absSource, O_RDONLY);
    int fdDest = open(absDest, O_CREAT | O_WRONLY, 0666);
    struct stat st;
    stat(sourcePath, &st);
    __off_t srcSize = st.st_size;
    sendfile(fdDest, fdSrc, NULL, srcSize);
    close(fdSrc);
    close(fdDest);
}

/*
 * Like mv in bash, except arguments are always assumed to be relative paths.
 */
void moveFile(char *sourcePath, char *destinationPath) {
    char absSource[PATH_MAX];
    char absDest[PATH_MAX];
    printf("apples");

    getcwd(absDest, sizeof(absDest));
    strcat(absDest, "/");
    strcpy(absSource, absDest);
    strcat(absSource, sourcePath);
    strcat(absDest, destinationPath);
    printf(absDest);
    rename(absSource, absDest);
}

/*
 * Deletes regular files.
 */
void deleteFile(char *filename) {
    char absPath[PATH_MAX];
    struct stat fileStat;

    getcwd(absPath, sizeof(absPath));
    strcat(absPath, "/");
    strcat(absPath, filename);

    stat(absPath, &fileStat);
    if (S_ISREG(fileStat.st_mode)) {
        unlink(absPath);
    }
    else {
        rmdir(absPath);
    }
}

/*
 * Prints the contents of files to STDOUT
 */
void displayFile(char *filename) {
    char absPath[PATH_MAX];
    char buff[5];
    struct stat fileStat;

    getcwd(absPath, sizeof(absPath));
    strcat(absPath, "/");
    strcat(absPath, filename);

    if (stat(filename, &fileStat) == 0) {
        int fd = open(absPath, O_RDONLY);
        while (read(fd, buff, 1) != 0) {
            write(STDOUT_FILENO, buff, 1);
        }
        close(fd);
    }
}