#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
} Process;

void round_robin(Process processes[], int n) {
    int remaining_processes = n;
    int current_time = 0;
    
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                int execute_time = (processes[i].remaining_time < TIME_QUANTUM) ? 
                                   processes[i].remaining_time : TIME_QUANTUM;
                
                printf("Executing process %d for %d units\n", processes[i].pid, execute_time);
                
                processes[i].remaining_time -= execute_time;
                current_time += execute_time;
                
                if (processes[i].remaining_time == 0) {
                    printf("Process %d completed at time %d\n", processes[i].pid, current_time);
                    remaining_processes--;
                }
            }
        }
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
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    round_robin(processes, n);
    
    return 0;
}
