#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Current process Id : %d\n", getpid());
    pid_t childProcessId = fork();
    if (childProcessId < 0) {
        printf("Failed to Create a new Process\n");
    } else if (childProcessId == 0) {
        printf("Child Process Id : %d Its parent ID : %d\n", getpid(), getppid());
    } else if (childProcessId > 0) {
        printf("Parent Process Id : %d Its Child Process ID : %d\n", getpid(), childProcessId);
    }
    return 0;
}
