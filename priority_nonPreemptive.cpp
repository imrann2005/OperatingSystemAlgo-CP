#include <iostream>

using namespace std;

void displayTable(struct Process*p,int n);
void displayMetrics();
void displayGanttChart();
void sortByPriorityAt(struct Process *p, int n);

struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int priority;
    int completed = 0;
};

struct ganttTime{
    string p;
    int st;
    int end;
}time[100];

int tidx = 0;

int main()
{
    int n;
    cout << "Enter Number of Processes ";
    cin >> n;
    //struct Process *p = (struct Process *)malloc(n * sizeof(struct Process));
    struct Process *p = new Process[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cout << "\nEnter Arrival Time of Process P" << i + 1 << " ";
        cin >> p[i].at;
        cout << "\nEnter Burst Time of Process P" << i + 1 << " ";
        cin >> p[i].bt;
        cout << "\nEnter Priority Of Process P" << i + 1 << " ";
        cin >> p[i].priority;
    }

    sortByPriorityAt(p, n);
    int c = 0;
    int t = 0;
    while (c < n)
    {
        /* code */
        int idx = -1;
        int mxp = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].completed == 0)
            {
                if(idx==-1 || p[i].priority > mxp || (p[i].priority==mxp && p[i].at < p[idx].at)){
                    idx = i;
                    mxp = p[i].priority;
                }
            }
        }
        if(idx != -1){
            time[tidx].st = t;
            t += p[idx].bt;
            
            p[idx].completed = 1;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].wt;
            time[tidx].end = p[idx].ct;
            time[tidx].p = "P"+to_string(p[idx].pid);
            tidx++;
            c++;
        }
        else{
            time[tidx].st = t;
            t++;
            time[tidx].end = t;
            time[tidx].p = "IDLE";
            tidx++;
        }
    }
    displayTable(p,n);
    return 0;
}

void sortByPriorityAt(struct Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if ((p[j].at > p[j + 1].at) || (p[j].at == p[j + 1].at && p[j].priority < p[j + 1].priority))
            {
                struct Process t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
            }
        }
    }
}

void displayTable(struct Process *p,int n){
    cout<<"\nPID\tPriority\tAt\tBt\tCt\tTat\tWt\tRt\t\n";
    for (int i = 0; i < n; i++)
    {
        cout<<p[i].pid<<"\t\t"<<p[i].priority<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<p[i].rt<<"\n";
    }
    
}