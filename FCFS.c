#include <stdio.h>

void FCFS() {
    int n, i, j;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int at[n], bt[n], ct[n], wt[n], tat[n], rt[n];
    int process[n];
    
    printf("Enter Arrival time and Burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] Arrival time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst time: ", i+1);
        scanf("%d", &bt[i]);
        process[i] = i;
    }
    
    // Sort processes based on arrival time using selection sort
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[process[i]] > at[process[j]]) {
                int temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
    
    // Calculate completion time
    int current_time = 0;
    for (i = 0; i < n; i++) {
        int idx = process[i];
        
        // If there's a gap between processes
        if (current_time < at[idx]) {
            current_time = at[idx];
        }
        
        // Response time = time when process first gets CPU - arrival time
        rt[idx] = current_time - at[idx];
        
        // Completion time
        current_time += bt[idx];
        ct[idx] = current_time;
        
        // Turnaround time = completion time - arrival time
        tat[idx] = ct[idx] - at[idx];
        
        // Waiting time = turnaround time - burst time
        wt[idx] = tat[idx] - bt[idx];
        
        // Sum for averages
        avg_wt += wt[idx];
        avg_tat += tat[idx];
        avg_rt += rt[idx];
    }
    
    // Calculate averages
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    
    // Display results in tabular form
    printf("\n+------+--------------+------------+------------------+--------------+------------------+---------------+\n");
    printf("| Proc | Arrival Time | Burst Time | Completion Time  | Waiting Time | Turnaround Time | Response Time |\n");
    printf("+------+--------------+------------+------------------+--------------+------------------+---------------+\n");
    
    for (i = 0; i < n; i++) {
        printf("| P[%d] | %-12d | %-10d | %-16d | %-12d | %-16d | %-13d |\n", 
               i+1, at[i], bt[i], ct[i], wt[i], tat[i], rt[i]);
    }
    
    printf("+------+--------------+------------+------------------+--------------+------------------+---------------+\n");
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}

int main() {
    FCFS();
    return 0;
}