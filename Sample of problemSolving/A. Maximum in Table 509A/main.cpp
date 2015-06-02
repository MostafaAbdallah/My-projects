/**
    Problem Name: A. Maximum in Table 509 A
    Target: 2D Array (Vector)
 **/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 0;
    int maxnum = 1;
    cin>>n;
    int **t = new int*[n];



    for(int i = 0; i < n; ++i){
        t[i] = new int[n];
    }
    for(int i = 0; i < n; ++i){
        t[0][i] = 1;
        t[i][0] = 1;
    }
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < n; ++j){
              //  cout<<t[i-1][j] << "----" << t[i][j-1] <<endl;
            t[i][j] = t[i-1][j]  + t[i][j-1] ;
            if(t[i][j] > maxnum)
                maxnum = t[i][j];
        }

    }

    cout << maxnum <<endl;

    return 0;
}
