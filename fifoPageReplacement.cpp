#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Enter Size of Page Ref String\n";
    cin >> n;
    cout << "Enter Page Ref String\n";
    int pg[n];
    for (int i = 0; i < n; i++)
    {
        cin >> pg[i];
    }
    int f;
    cout << "Enter No. of Frames\n";
    cin >> f;
    int frames[f];
    int p = 0;
    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
    }
    int hit = 0, miss = 0;
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        int page = pg[i];
        for (int j = 0; j < f; j++)
        {
            if (page == frames[j])
            {
                flag = 1;
                hit++;
                break;
            }
        }
        if (flag == 0)
        {
            /*miss*/
            miss++;
            frames[p] = page;
            p = (p + 1) % f;
        }
        cout << "Page " << page << " => ";
        for (int k = 0; k < f; k++)
        {
            (frames[k] == -1) ? (cout << "- ") : (cout << frames[k] << " ");
        }
        cout << endl;
    }
    cout << "Hit " << hit << " miss " << miss << endl;
    return 0;
}