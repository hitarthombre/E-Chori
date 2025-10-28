#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int completed;
};

void calculateSJF(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    float totalTurnaround = 0, totalWaiting = 0;

    for (int i = 0; i < n; i++) {
        processes[i].completed = 0;
    }
    printf("\nSJF Scheduling Results:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("------------------------------------------------------------\n");

    while (completed < n) {
        int shortest = -1;
        int shortestBurst = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime &&
                !processes[i].completed &&
                processes[i].burst < shortestBurst) {
                shortestBurst = processes[i].burst;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }
        processes[shortest].completion = currentTime + processes[shortest].burst;
        processes[shortest].turnaround = processes[shortest].completion - processes[shortest].arrival;
        processes[shortest].waiting = processes[shortest].turnaround - processes[shortest].burst;
        processes[shortest].completed = 1;
        currentTime = processes[shortest].completion;
        completed++;
        totalTurnaround += processes[shortest].turnaround;
        totalWaiting += processes[shortest].waiting;

        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[shortest].pid,
               processes[shortest].arrival,
               processes[shortest].burst,
               processes[shortest].completion,
               processes[shortest].turnaround,
               processes[shortest].waiting);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
    printf("Average Waiting Time: %.2f\n", totalWaiting / n);
}

void sortByArrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
void displayGanttChart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf("-----------\n");
    struct Process *executionOrder = (struct Process*)malloc(n * sizeof(struct Process));
    int currentTime = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        processes[i].completed = 0;
    }


    int orderIndex = 0;
    while (completed < n) {
        int shortest = -1;
        int shortestBurst = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime &&
                !processes[i].completed &&
                processes[i].burst < shortestBurst) {
                shortestBurst = processes[i].burst;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }
        executionOrder[orderIndex] = processes[shortest];
        orderIndex++;
        processes[shortest].completed = 1;
        currentTime += processes[shortest].burst;
        completed++;
    }
    for (int i = 0; i < n; i++) {
        printf("| P%d ", executionOrder[i].pid);
    }
    printf("|\n");
    currentTime = 0;
    printf("%d", currentTime);

    for (int i = 0; i < n; i++) {
        if (currentTime < executionOrder[i].arrival) {
            currentTime = executionOrder[i].arrival;
        }
        currentTime += executionOrder[i].burst;
        printf("\t%d", currentTime);
    }
    printf("\n");
    free(executionOrder);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: Number of processes must be greater than 0\n");
        return 1;
    }
    struct Process *processes = (struct Process*)malloc(n * sizeof(struct Process));
    if (processes == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival);

        if (processes[i].arrival < 0) {
            printf("Error: Arrival time cannot be negative\n");
            free(processes);
            return 1;
        }
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst);

        if (processes[i].burst <= 0) {
            printf("Error: Burst time must be greater than 0\n");
            free(processes);
            return 1;
        }
    }
    sortByArrival(processes, n);
    calculateSJF(processes, n);
    displayGanttChart(processes, n);
    free(processes);
    return 0;
}

