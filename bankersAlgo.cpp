#include <iostream>
using namespace std;

int main()
{
    int np, nr;
    int allocation[10][10];
    int max[10][10];
    int need[10][10];
    int available[10];
    int flag = 0;
    int finish[10];
    int safeseq[10];
    int k = 0;
    cout << "Enter No of process\n";
    cin >> np;
    cout << "Enter No. of Resources\n";
    cin >> nr;
    cout << "Enter Allocation Matrix\n";
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            cin >> allocation[i][j];
        }
    }
    cout << "Enter Max Matrix\n";
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            cin >> max[i][j];
        }
    }
    cout << "Enter Available Resources\n";
    for (int i = 0; i < nr; i++)
    {
        cin >> available[i];
    }

    cout << "Need Matrix\n";
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < np; i++)
    {
        finish[i] = 0;
    }

    for (int i = 0; i < np; i++)
    {
        flag = 0;
        if (finish[i] == 0)
        {
            for (int j = 0; j < nr; j++)
            {
                if (need[i][j] > available[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                finish[i] = 1;
                for (int j = 0; j < nr; j++)
                {
                    available[j] += allocation[i][j];
                }
                safeseq[k++] = i;
                i=-1;
            }
        }
    }

    int deadloack = 0;
    for (int i = 0; i < np; i++)
    {
        if (finish[i] == 0)
        {
            deadloack = 1;
            break;
        }
    }
    if (deadloack)
    {
        cout << "System is in Deadlock!\n";
    }
    else
    {
        cout << "System not in deadlock\n";
        cout<<"Safe Sequence\t";
        for (int i = 0; i < np; i++)
        {
            cout << " ->P" << safeseq[i];
        }
    }

    return 0;
}