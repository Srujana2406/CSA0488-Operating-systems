#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES];

bool isSafeState(int processes[], int num_processes, int num_resources) 
{
    int work[num_resources];
    bool finish[num_processes];

    for (int i = 0; i < num_resources; ++i)
        work[i] = available[i];
    for (int i = 0; i < num_processes; ++i)
        finish[i] = false;

    int count = 0;
    while (count < num_processes) 
	{
        bool found = false;
        for (int i = 0; i < num_processes; ++i) 
		{
            if (!finish[i]) 
			{
                int j;
                for (j = 0; j < num_resources; ++j)
                    if (need[i][j] > work[j])
                        break;
                if (j == num_resources) 
				{
                    for (int k = 0; k < num_resources; ++k)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) 
		{
            return false;
        }
    }
    return true;
}

bool requestResources(int process_id, int request[], int num_resources) 
{
  
    for (int i = 0; i < num_resources; ++i)
        if (request[i] > need[process_id][i])
            return false;

    for (int i = 0; i < num_resources; ++i)
        if (request[i] > available[i])
            return false;

    for (int i = 0; i < num_resources; ++i) 
	{
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    if (!isSafeState(NULL, 0, num_resources)) 
	{
        for (int i = 0; i < num_resources; ++i) 
		{
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        return false;
    }

    return true;
}

int main() {
    int num_processes, num_resources;

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter available resources: ");
    for (int i = 0; i < num_resources; ++i)
        scanf("%d", &available[i]);

    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &maximum[i][j]);

    printf("Enter allocation for each process:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }

    // Simulate resource requests
    int process_id;
    int request[MAX_RESOURCES];
    printf("Enter process ID (0-%d) and resource request:\n", num_processes - 1);
    scanf("%d", &process_id);
    for (int i = 0; i < num_resources; ++i)
        scanf("%d", &request[i]);

    if (requestResources(process_id, request, num_resources))
        printf("Request granted.\n");
    else
        printf("Request denied.\n");

    return 0;
}

