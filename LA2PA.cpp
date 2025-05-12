#include <iostream>
using namespace std;

int main()
{
    int np;
    cout << "Enter Number of Pages\n";
    cin >> np;
    int size;
    cout << "Enter Page/Frame Size\n";
    cin >> size;
    int la;
    cout << "Enter Logical Address\n";
    cin >> la;
    int pageTable[10];
    for (int i = 0; i < np; i++)
    {
        cout << "Enter Frame No. for Page " << i << ": ";
        cin >> pageTable[i];
    }
    int pgNum = la / size;
    if (pgNum >= np)
    {
        cout << "Enter Valid Logical Address\n";
    }
    else
    {
        int offset = la % size;
        int frameNum = pageTable[pgNum];
        int pa = frameNum*size + offset;
        cout<<"Physical Address "<<pa<<endl;
    }
}