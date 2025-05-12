#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int tbt;
    int ct;
};

void print_gantt_chart(int timeline[], int timeline_pid[], int timeline_size, int mn)
{
    int i;
    printf("\nGantt Chart:\n");
    printf(" ");
    for (i = 0; i < timeline_size; i++)
    {
        printf(" ----");
    }
    printf(" \n|");
    for (i = 0; i < timeline_size; i++)
    {
        printf(" P%d |", timeline_pid[i]);
    }
    printf("\n ");
    for (i = 0; i < timeline_size; i++)
    {
        printf(" ----");
    }
    printf("\n");
    printf("%d", mn);
    for (i = 0; i < timeline_size; i++)
    {
        printf("   %d", timeline[i]);
    }
    printf("\n");
}

int main()
{
    int n, tq, i, time = 0, completed = 0, index = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process *p = (struct process *)malloc(n * sizeof(struct process));
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    int mn = 9999;
    for (i = 0; i < n; i++)
    {
        printf("Enter process id: ");
        scanf("%d", &p[i].pid);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        p[i].tbt = p[i].bt;
        mn = (mn < p[i].at) ? mn : p[i].at;
    }
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int timeline[1000], timeline_pid[1000], timeline_size = 0;
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};

    for (i = 0; i < n; i++)
    {
        if (p[i].at == mn)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }
    time = mn;
    while (completed < n)
    {
        if (front == rear)
        {
            time++;
            continue;
        }

        int current = queue[front++];
        if (p[current].bt > tq)
        {
            time += tq;
            p[current].bt -= tq;
        }
        else
        {
            time += p[current].bt;
            p[current].bt = 0;
            p[current].tat = time - p[current].at;
            p[current].wt = p[current].tat - p[current].tbt;
            p[current].ct = time;
            completed++;
        }

        timeline[timeline_size] = time;
        timeline_pid[timeline_size] = p[current].pid;
        timeline_size++;

        for (i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].at <= time && p[i].bt > 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[current].bt > 0)
        {
            queue[rear++] = current;
        }
    }

    printf("\nProcess ID\tAT\tBT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].tbt, p[i].tat, p[i].wt);
    }

    print_gantt_chart(timeline, timeline_pid, timeline_size, mn);
    free(p);
    return 0;
}
