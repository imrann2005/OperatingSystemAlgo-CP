#include<iostream>

using namespace std;

int main(){
    int n;
    cout<<"Enter The Size of Request List\n";
    cin>>n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout<<"Enter Request at index : "<<i<<endl;
        cin >> a[i];
    }
    int head;
    cout<<"Enter initial head position\n";
    cin>>head;

    int total = 0;

    for (int i = 0; i < n; i++)
    {
        total += abs(a[i]-head);
        head = a[i];
        cout<<"Current Head After Request "<<i<<" "<<head<<endl;
    }
    
    cout<<"Total Head Movement\n"<<total<<endl;

    return 0;
}