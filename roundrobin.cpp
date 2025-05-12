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
    while (1)
    {
        /* code */
        int d = 1;
        for (int i = 0; i < 4; i++)
        {
            if(p[i].rbt > 0 && p[i].at <= t){
                d = 0;
                if(p[i].rbt > q){
                    t += q;
                    p[i].rbt -= q;
                }
                else{
                    t += p[i].rbt;
                    p[i].rbt = 0;
                    p[i].ct = t;
                }
            }
            
        }

        if(d){
            break;
        }
        
    }
    for (int i = 0; i < 4; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    cout<<"\nP ID\tAt\tBt\tCt\tTat\tWt\t\n";
    for (int i = 0; i < 4; i++)
    {
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<"\n";
    }
    
    return 0;
}