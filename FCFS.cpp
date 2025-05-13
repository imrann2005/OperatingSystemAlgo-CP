#include<iostream>

using namespace std;
/*FCFS Priority Scheduling*/

struct p
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int st;
}p[5];


int main(){
    for (int i = 0; i < 5; i++)
    {
        p[i].pid = i;
        cout<<"Enter Arrival Time for Process "<<p[i].pid<<" ";
        cin>>p[i].at;
        cout<<"Enter Burst Time for Process "<<p[i].pid<<" ";
        cin>>p[i].bt;

    }
    //Sort by At
    for (int i = 0; i < 5; i++)
    {
        /* code */
        if(i==0){
            p[i].ct = p[i].at + p[i].bt;
        }
        else{
            p[i].ct = max(p[i].at,p[i-1].ct) + p[i].bt;
        }
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
    }
    cout<<"\nP ID\tAt\tBt\tCt\tTat\tWt\tRt\t\n";
    for (int i = 0; i < 5; i++)
    {
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<p[i].rt<<"\n";
    }
    
    
    return 0;
}