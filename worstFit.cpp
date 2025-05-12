#include <iostream>

using namespace std;

int main()
{
    int np;
    cout << "Enter the no. of process\n";
    cin >> np;
    int nb;
    cout << "Enter the no of blocks\n";
    cin >> nb;
    int p[np];
    int b[nb];
    int flag[nb];
    int bn[np];
    int bf[nb];
    for (int i = 0; i < np; i++)
    {
        cout << "Enter Process Size " << i << endl;
        cin >> p[i];
    }
    for (int i = 0; i < nb; i++)
    {
        cout << "Enter Block Size" << i << endl;
        cin >> b[i];
    }
    for (int i = 0; i < np; i++)
    {
        bn[i] = 0;
    }
    for (int i = 0; i < nb; i++)
    {
        flag[i] = 0;
        bf[i] = 0;
    }

    for (int i = 0; i < np; i++)
    {
        int idx = -1;
        int mx = -1;
        for (int j = 0; j < nb; j++)
        {
            if (flag[j] == 0 && b[j] > mx && p[i] <= b[j])
            {
                mx = b[j];

                idx = j;
            }
        }

        if (idx != -1)
        {
            bn[i] = idx;
            flag[idx] = 1;
            bf[idx] = b[idx] - p[i];
        }
        else
        {
            bn[i] = -1;
        }
    }

    cout << "Process Size\tBlock Num\tFragmentation\t\n";
    for (int i = 0; i < np; i++)
    {
        cout << p[i] << "\t\t" << bn[i] << "\t\t" << ((bn[i] == -1) ? 0 : bf[bn[i]] )<< "\n";
    }

    return 0;
}
