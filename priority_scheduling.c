#include <stdio.h>

struct process {
    int pid;
    int at;      // Arrival Time
    int bt;      // Burst Time
    int priority; // Priority
    int ct;      // Completion Time
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
    int rt;      // Response Time
    int is_completed;
};

void PriorityScheduling() {
    int n, i, j;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct process p[n];
    
    for (i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter arrival time for P[%d]: ", i+1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for P[%d]: ", i+1);
        scanf("%d", &p[i].bt);
        printf("Enter priority for P[%d] (lower value means higher priority): ", i+1);
        scanf("%d", &p[i].priority);
        p[i].is_completed = 0;
    }
    
    int current_time = 0;
    int completed = 0;
    
    // Process all jobs until all are completed
    while (completed != n) {
        // Find the process with the highest priority (lowest priority number) among arrived processes
        int highest_priority_idx = -1;
        int highest_priority = 9999;
        
        for (i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].is_completed == 0) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    highest_priority_idx = i;
                }
                // If priority is same, use arrival time as tie-breaker
                else if (p[i].priority == highest_priority && p[i].at < p[highest_priority_idx].at) {
                    highest_priority_idx = i;
                }
            }
        }
        
        // If no process is available at current time
        if (highest_priority_idx == -1) {
            current_time++;
            continue;
        }
        
        // Execute the process with highest priority
        // Response time is when process first gets CPU - arrival time
        p[highest_priority_idx].rt = current_time - p[highest_priority_idx].at;
        
        // Execute the process
        current_time += p[highest_priority_idx].bt;
        
        // Update completion time
        p[highest_priority_idx].ct = current_time;
        
        // Update turnaround time
        p[highest_priority_idx].tat = p[highest_priority_idx].ct - p[highest_priority_idx].at;
        
        // Update waiting time
        p[highest_priority_idx].wt = p[highest_priority_idx].tat - p[highest_priority_idx].bt;
        
        // Mark process as completed
        p[highest_priority_idx].is_completed = 1;
        completed++;
        
        // Update average metrics
        avg_wt += p[highest_priority_idx].wt;
        avg_tat += p[highest_priority_idx].tat;
        avg_rt += p[highest_priority_idx].rt;
    }
    
    // Calculate average metrics
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    
    // Display results in tabular form
    printf("\n+------+--------------+------------+----------+------------------+--------------+------------------+---------------+\n");
    printf("| Proc | Arrival Time | Burst Time | Priority | Completion Time  | Waiting Time | Turnaround Time | Response Time |\n");
    printf("+------+--------------+------------+----------+------------------+--------------+------------------+---------------+\n");
    
    // Sort processes by pid for display
    struct process temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (p[j].pid > p[j+1].pid) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        printf("| P[%d] | %-12d | %-10d | %-8d | %-16d | %-12d | %-16d | %-13d |\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].wt, p[i].tat, p[i].rt);
    }
    
    printf("+------+--------------+------------+----------+------------------+--------------+------------------+---------------+\n");
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}

int main() {
    PriorityScheduling();
    return 0;
}