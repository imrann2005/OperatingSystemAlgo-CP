#include<iostream>

using namespace std;

int main(){
    int np;
    int nb;
    cout<<"Enter no. of processes\n";
    cin>>np;
    cout<<"Enter no. of blocks\n";
    cin>>nb;
    int b[nb];
    int p[np];
    int bf[nb];
    int bn[np];
    int flag[np];
    for (int i = 0; i < np; i++)
    {
        cout<<"Enter Process Size\n";
        cin>>p[i];
    }
    for (int i = 0; i < nb; i++)
    {
        /* code */
        cout<<"Enter Block Size\n";
        cin>>b[i];
    }
    
    
    for (int i = 0; i < np; i++)
    {
        flag[i] = 0;
        bn[i] = 0;
    }
    for (int i = 0; i < nb; i++)
    {
        bf[i] = 0;
    }

    for (int i = 0; i < np; i++)
    {
        int mn = 1000;
        int idx = -1;
        for (int j = 0; j < nb; j++)
        {
            if(flag[j]==0 && b[j] < mn && p[i]<=b[j]){
                mn = b[j];
                idx = j;
            }
        }
        if(idx!=-1){
           bn[i] = idx; 
           flag[idx] = 1;
           bf[idx] = b[idx]-p[i];
        }
        else{
            bn[i] = -1;
        }
        
    }
    cout<<"Process Size\tBlock Num\tFragmentation\t\n";
    for (int i = 0; i < np; i++)
    {
        cout<<p[i]<<"\t\t"<<bn[i]<<"\t\t"<<bf[bn[i]]<<"\n";
    }
    
    
    return 0;
}
