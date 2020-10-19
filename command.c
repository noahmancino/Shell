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
    char dirPath[PATH_MAX];

    getcwd(dirPath, sizeof(dirPath));
    strcat(dirPath, "/");
    strcat(dirPath, dirName);

    // All permissions that don't conflict with umask will always be granted.
    if (mkdir(dirPath, 0777) == -1) {
        write(STDERR_FILENO, "File already exists.", 20);
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
    struct stat st2;
    stat(sourcePath, &st);
    stat(destinationPath, &st2);
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
    getcwd(absDest, sizeof(absDest));
    strcat(absDest, "/");
    strcpy(absSource, absDest);
    strcat(absSource, sourcePath);
    strcat(absDest, destinationPath);
    rename(absSource, absDest);
}

void deleteFile(char *filename) {
    char absPath[PATH_MAX];
    getcwd(absPath, sizeof(absPath));
    strcat(absPath, "/");
    strcat(absPath, filename);
    struct stat fileStat;
    stat(absPath, &fileStat);
    if (S_ISREG(fileStat.st_mode)) {
        unlink(absPath);
    }
    else {
        rmdir(absPath);
    }
}

void displayFile(char *filename) {
    // TODO: Make sure file exists.
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