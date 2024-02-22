#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int burst_time;
    int executed;
} Process;

int findShortestExecutionTimeProcess(Process processes[], int n) {
    int shortest_time = -1;
    int shortest_time_index = -1;
    for (int i = 0; i < n; i++) {
        if (!processes[i].executed && (shortest_time == -1 || processes[i].burst_time < shortest_time)) {
            shortest_time = processes[i].burst_time;
            shortest_time_index = i;
        }
    }
    return shortest_time_index;
}

void executeProcesses(Process processes[], int n) {
    int remaining_processes = n;
    int current_time = 0;
    
    while (remaining_processes > 0) {
        int index = findShortestExecutionTimeProcess(processes, n);
        if (index == -1)
            break;
        
        printf("Executing process %d with execution time %d\n", processes[index].pid, processes[index].burst_time);
        current_time += processes[index].burst_time;
        printf("Process %d completed at time %d\n", processes[index].pid, current_time);
        processes[index].executed = 1; 
        remaining_processes--;
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].executed = 0;
    }

    executeProcesses(processes, n);

    return 0;
}
