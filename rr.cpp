#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int burst;      // Burst time
    int remaining;  // Remaining time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};

void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0;
    int completed = 0;
   
    for(int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst;
        proc[i].waiting = 0;
        proc[i].turnaround = 0;
    }
   
    printf("\nGantt Chart:\n");
    printf("0");
   
    while(completed < n) {
        int allDone = 1;
       
        for(int i = 0; i < n; i++) {
            if(proc[i].remaining > 0) {
                allDone = 0;
               
                if(proc[i].remaining > quantum) {
                    printf(" -> P%d -> %d", proc[i].pid, time + quantum);
                    time += quantum;
                    proc[i].remaining -= quantum;
                } else {
                    printf(" -> P%d -> %d", proc[i].pid, time + proc[i].remaining);
                    time += proc[i].remaining;
                    proc[i].remaining = 0;
                    completed++;
                  
                    proc[i].turnaround = time;
                    proc[i].waiting = proc[i].turnaround - proc[i].burst;
                }
            }
        }
       
        if(allDone) break;
    }
    printf("\n");
}
int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n); 
    printf("Enter time quantum: ");
    scanf("%d", &quantum); 
    struct Process proc[n];
   
    for(int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &proc[i].burst);
        proc[i].pid = i + 1;
    }
   
    roundRobin(proc, n, quantum);
   
    
    float total_waiting = 0, total_turnaround = 0;
   
    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    printf("-------\t-----\t-------\t----------\n");
   
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].burst,
               proc[i].waiting,
               proc[i].turnaround);
       
        total_waiting += proc[i].waiting;
        total_turnaround += proc[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
   
    return 0;
}

