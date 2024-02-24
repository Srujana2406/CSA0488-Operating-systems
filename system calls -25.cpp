#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void demonstrate_fcntl() {
    int fd;
    fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int flags;
    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File descriptor flags: %d\n", flags);

    close(fd);
}

void demonstrate_seek() {
    int fd;
    fd = open("testfile.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    off_t offset;
    offset = lseek(fd, 10, SEEK_SET);
    if (offset == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    printf("Current offset: %lld\n", (long long)offset);

    close(fd);
}

void demonstrate_stat() {
    struct stat fileStat;

    if (stat("testfile.txt", &fileStat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Number of Links: %d\n", (int)fileStat.st_nlink);
}

void demonstrate_opendir() {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
}

int main() {
    demonstrate_fcntl();
    demonstrate_seek();
    demonstrate_stat();
    demonstrate_opendir();

    return 0;
}

