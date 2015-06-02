#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int>t;
    int n = 0, m = 0;
   long long int counter = 0;
    int task = 0;
    bool flag = false;
    cin>>n>>m;
    for(int i = 1 ; i <= m ; ++i){
        cin>>task;
        t.push_back(task);
    }

    for(int i = 0; i < t.size(); ++i){
        if(i == 0){
            counter = t[0]-1;
        }
        else if(t[i] > t[i-1]){
            counter = counter + t[i] - t[i-1];
        }
        else if (t[i] < t[i-1]){
            int num = n - t[i-1];
            counter = counter + num + t[i] ;
        }
    }

    cout<<counter<<endl;
    return 0;
}
