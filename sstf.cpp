#include <iostream>

using namespace std;

int main(){
    int n;
    cout<<"Enter Number of Requests\n";
    cin>>n;
    int req[n];
    for (int i = 0; i < n; i++)
    {
        cin>>req[i];
    }
    int distance = 0;
    int mn = 1000;
    int pending = n;
    int head;
    cout<<"Enter Initial Head Position\n";
    cin>>head;
    int finish[n];
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    int idx = -1;
    while (pending > 0)
    {
        mn = 1000;
        for (int i = 0; i < n; i++)
        {
            int diff = abs(head - req[i]);
            if((finish[i]==0) && (diff < mn)){
                mn = diff;
                idx = i;
            }
        }
        cout<<" -> "<<head;
        distance += abs(head - req[idx]);
        finish[idx] = 1;
        head = req[idx];
        pending--;
    }
    cout<<" -> "<<head;
    cout<<"\nTotal Distance: "<<distance<<endl;
    return 0;
}