/**
   Problem Name: A. Gravity Flip
   Target:       Sort

**/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> cubes;
    int numCol = 0;
    int numCube = 0;

    cin>>numCol;

    for(int i = 0; i < numCol; ++i){
        cin >> numCube;
        cubes.push_back(numCube);
    }

    sort(cubes.begin(),cubes.end());

    for(int i = 0; i < numCol; ++i){
        cout << cubes[i] << " ";

    }

    return 0;
}
