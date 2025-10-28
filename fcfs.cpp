#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
};
void calculateFCFS(struct Process processes[], int n) {
    int currentTime = 0;
    float totalTurnaround = 0, totalWaiting = 0;
    printf("\nFCFS Scheduling Results:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("------------------------------------------------------------\n");
   
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }
        processes[i].completion = currentTime + processes[i].burst;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst; 
        currentTime = processes[i].completion; 
        totalTurnaround += processes[i].turnaround;
        totalWaiting += processes[i].waiting; 
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival,
               processes[i].burst,
               processes[i].completion,
               processes[i].turnaround,
               processes[i].waiting);
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
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");
    int currentTime = 0;
    printf("%d", currentTime); 
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival;
        }
        currentTime += processes[i].burst;
        printf("\t%d", currentTime);
    }
    printf("\n");
}
int main() {
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n); 
    struct Process *processes = (struct Process*)malloc(n * sizeof(struct Process));
   
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].pid = i + 1; 
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival); 
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst);
    }
    sortByArrival(processes, n);   
    calculateFCFS(processes, n);
    displayGanttChart(processes, n); 
    free(processes);
    return 0;
}

