#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int n;
    cout << "Enter Request List Size\n";
    cin >> n;
    int req[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Request " << i << " \n";
        cin >> req[i];
    }
    int head;
    cout << "Enter Initial Head Position\n";
    cin >> head;
    int curr = head;
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        t += abs(curr - req[i]);
        curr = req[i];
        cout<<"Head Position After Request "<<i+1<<" "<<curr<<endl;

    }
    cout<<"Total Displacement "<<t<<endl;
    return 0;
}