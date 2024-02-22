#include <stdio.h>

typedef struct {
    int pid;
    int burst_time;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sjf(Process processes[], int n) {
    
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (processes[j].burst_time > processes[j+1].burst_time) {
                swap(&processes[j], &processes[j+1]);
            }
        }
    }

    int current_time = 0;
    printf("Order of execution: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", processes[i].pid);
        current_time += processes[i].burst_time;
        printf("(Completion Time: %d)\n", current_time);
    }
}

int main() {
    int n;
    Process processes[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    sjf(processes, n);

    return 0;
}
