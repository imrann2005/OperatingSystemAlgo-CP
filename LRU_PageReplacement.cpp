#include<iostream>

using namespace std;

int main(){
    int F[10],P[30],time[10];
    int np,nf;
    int flag,flag2;
    int cnt=0,faults=0,loc;
    cout<<"Enter No. of Pages\n";
    cin>>np;
    cout<<"Enter Page Ref String\n";
    for (int i = 0; i < np; i++)
    {
        cin>>P[i];
    }
    cout<<"Enter No. of Frames\n";
    cin>>nf;
    for (int i = 0; i < nf ; i++)
    {
        /* code */
        time[i] = 0;
        F[i] = -1;
    }

    cout<<"Frame Contents\n";

    for (int i = 0; i < np; i++)
    {
        flag=flag2=0;
        for (int j = 0;  j < nf;  j++)
        {
            if(P[i]==F[j]){
                cnt++;
                time[j] = cnt;
                flag=flag2=1;
                break;
            }
        }
        if(flag2==0){
            for (int j = 0; j < nf; j++)
            {
                if(F[j]==-1){
                    F[j] = P[i];
                    flag=flag2=1;
                    cnt++;
                    time[j] = cnt;
                    faults++;
                    break;
                }
            }
            
        }
        if(flag2==0){
            int mn = 1000;
            for(int j=0;j<nf;j++){
                if(mn > time[j]){
                    mn = time[j];
                    loc = j;
                }
            }
            F[loc] = P[i];
            cnt++;
            time[loc] = cnt;
            faults++;
            
        }
        cout<<"Page "<<P[i]<<" =>\t";
        for (int k = 0; k < nf; k++)
        {
            if(F[k]!=-1){
                cout<<F[k]<<" ";
            }
            else cout<<-1<<" ";
        }
        cout<<endl;
    }
    cout<<"MISS "<<faults<<endl;
    cout<<"HITS "<<np-faults<<endl;
    
    return 0;
}