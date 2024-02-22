#include<stdio.h>
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

void calculateTimes(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

void calculateAverages(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    calculateTimes(processes, n, waiting_time, turnaround_time);
    float average_waiting_time = 0, average_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        average_waiting_time += waiting_time[i];
        average_turnaround_time += turnaround_time[i];
    }

    average_waiting_time /= n;
    average_turnaround_time /= n;

    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

void displaySchedule(struct Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
            i == 0 ? 0 : (processes[i - 1].burst_time + processes[i - 1].arrival_time),
            processes[i].burst_time + (i == 0 ? 0 : (processes[i - 1].burst_time + processes[i - 1].arrival_time))
        );
    }
}

int main() {

    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    displaySchedule(processes, n);
    calculateAverages(processes, n);

    return 0;
}
