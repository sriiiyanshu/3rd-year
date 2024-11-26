#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    int remainingTime;
    int isCompleted;
};

int findNextProcess(struct Process proc[], int n, int currentTime) {
    int highestPriorityIdx = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrivalTime <= currentTime && proc[i].isCompleted == 0) {
            if (highestPriorityIdx == -1 || proc[i].priority > proc[highestPriorityIdx].priority) {
                highestPriorityIdx = i;
            }
        }
    }
    return highestPriorityIdx;
}

void calculateCompletionTime(struct Process proc[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int idx = findNextProcess(proc, n, currentTime);
        
        if (idx == -1) { 
            currentTime++;
            continue;
        }

        proc[idx].remainingTime--;
        if (proc[idx].remainingTime == 0) {
            currentTime++;
            proc[idx].completionTime = currentTime;
            proc[idx].isCompleted = 1;
            completedProcesses++;
        } else {
            currentTime++;
        }
    }
}

void calculateTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
    }
}

void calculateWaitingTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;
    }
}

void displayTable(struct Process proc[], int n) {
    printf("\nProcess ID\tArrival Time\tPriority\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                proc[i].id, proc[i].arrivalTime, proc[i].priority, proc[i].burstTime, 
                proc[i].completionTime, proc[i].turnAroundTime, proc[i].waitingTime);
    }
}

void displayAvgTime(struct Process proc[], int n) {
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnAroundTime += proc[i].turnAroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time, burst time and priority for Process %d: ", proc[i].id);
        scanf("%d", &proc[i].arrivalTime);
        scanf("%d", &proc[i].burstTime);
        scanf("%d", &proc[i].priority);
        proc[i].isCompleted = 0;
        proc[i].remainingTime = proc[i].burstTime;
    }

    calculateCompletionTime(proc, n);
    calculateTurnAroundTime(proc, n);
    calculateWaitingTime(proc, n);

    displayTable(proc, n);
    displayAvgTime(proc, n);

    return 0;
}
