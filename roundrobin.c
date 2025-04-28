#include <stdio.h>

void RoundRobin() {
    int n, tq, i, j, time = 0;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    
    int at[n], bt[n], rt[n], ct[n], wt[n], tat[n], resp_t[n];
    int process[n];
    int first_time[n];
    
    printf("Enter Arrival time and Burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d] Arrival time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst time: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        process[i] = i;
        first_time[i] = -1; // Initialize first_time to -1 (not started yet)
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
    
    // Initialize time to first process arrival time
    time = at[process[0]];
    
    // Create queue for ready processes
    int queue[100], front = 0, rear = 0;
    int completed = 0;
    int current_process = -1;
    
    // Add first process to queue
    queue[rear] = process[0];
    rear = (rear + 1) % 100;
    
    while (completed < n) {
        // Get next process from queue
        if (front != rear) {
            current_process = queue[front];
            front = (front + 1) % 100;
            
            // Record first time this process gets CPU if not recorded yet
            if (first_time[current_process] == -1) {
                first_time[current_process] = time;
                resp_t[current_process] = first_time[current_process] - at[current_process];
            }
            
            // Execute process for time quantum or remaining time
            if (rt[current_process] <= tq) {
                time += rt[current_process];
                rt[current_process] = 0;
                completed++;
                
                // Record completion time
                ct[current_process] = time;
                tat[current_process] = ct[current_process] - at[current_process];
                wt[current_process] = tat[current_process] - bt[current_process];
            } else {
                time += tq;
                rt[current_process] -= tq;
            }
            
            // Check for any new arrivals while the current process was executing
            for (i = 0; i < n; i++) {
                if (rt[i] > 0 && at[i] <= time && i != current_process) {
                    // Check if process is already in queue
                    int in_queue = 0;
                    for (j = front; j != rear; j = (j + 1) % 100) {
                        if (queue[j] == i) {
                            in_queue = 1;
                            break;
                        }
                    }
                    if (!in_queue) {
                        queue[rear] = i;
                        rear = (rear + 1) % 100;
                    }
                }
            }
            
            // Add current process back to queue if it still has remaining time
            if (rt[current_process] > 0) {
                queue[rear] = current_process;
                rear = (rear + 1) % 100;
            }
        } else {
            // If queue is empty, find the next process to arrive
            int next_arrival = -1;
            int min_arrival = 9999;
            for (i = 0; i < n; i++) {
                if (rt[i] > 0 && at[i] > time && at[i] < min_arrival) {
                    min_arrival = at[i];
                    next_arrival = i;
                }
            }
            
            if (next_arrival != -1) {
                time = at[next_arrival];
                queue[rear] = next_arrival;
                rear = (rear + 1) % 100;
            }
        }
    }
    
    // Calculate averages
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += resp_t[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    
    // Display results in tabular form
    printf("\n+------+--------------+------------+------------------+--------------+------------------+---------------+\n");
    printf("| Proc | Arrival Time | Burst Time | Completion Time  | Waiting Time | Turnaround Time | Response Time |\n");
    printf("+------+--------------+------------+------------------+--------------+------------------+---------------+\n");
    
    for (i = 0; i < n; i++) {
        printf("| P[%d] | %-12d | %-10d | %-16d | %-12d | %-16d | %-13d |\n", 
               i+1, at[i], bt[i], ct[i], wt[i], tat[i], resp_t[i]);
    }
    
    printf("+------+--------------+------------+------------------+--------------+------------------+---------------+\n");
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}

int main() {
    RoundRobin();
    return 0;
}