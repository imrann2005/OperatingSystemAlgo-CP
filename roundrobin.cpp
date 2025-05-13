#include<iostream>
#include<bits/stdc++.h>

using namespace std;

struct p
{
    /* data */
    int pid;
    int at;
    int bt;
    int rbt;
    int ct;
    int tat;
    int wt;
    int rt;
    int start_time;
}p[4];


int main(){
    int q;
    cout<<"Enter Time Quantum\n";
    cin>>q;
    for (int i = 0; i < 4; i++)
    {
        p[i].pid = i;
        cout<<"Enter Arrival Time for P"<<p[i].pid<<" ";
        cin>>p[i].at;
        cout<<"Enter Burst Time for P"<<p[i].pid<<" ";
        cin>>p[i].bt;
        p[i].rbt = p[i].bt;
    }
    int t = 0;
    int d = 0;
    int c = 0;
    while (c<4)
    {
        d = 0;
        for (int i = 0; i < 4; i++)
        {
            if(p[i].at <= t && p[i].rbt > 0){
                d = 1;
                if(p[i].rbt == p[i].bt){
                    p[i].start_time = t;
                }
                if(p[i].rbt > q){
                    p[i].rbt -=  q;
                    t += q;
                }
                else{
                    t += p[i].rbt;
                    p[i].rbt = 0;
                    c++;
                    p[i].ct = t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    p[i].rt = p[i].start_time - p[i].at;
                }
            }
        }
        if(d==0)t++;
    }

    cout<<"\nP ID\tAt\tBt\tCt\tTat\tWt\t\n";
    for (int i = 0; i < 4; i++)
    {
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<"\n";
    }
    
    return 0;
}