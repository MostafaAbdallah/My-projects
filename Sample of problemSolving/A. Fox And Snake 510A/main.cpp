/**
    Problem Name: A. Fox And Snake 510A
    Target :      Loops And Array Implementation

**/


#include <iostream>

using namespace std;

int main()
{
    int row = 0;
    int col = 0;
    bool Start = false;
    bool End = true;
    cin >> row >> col;

    for(int i = 0; i < row; ++i){

        for(int j = 0; j < col; ++j){
            if(i % 2 == 0){
                cout<<"#";
            }
            else if((j == 0 && Start) || (j == col-1 && End)){
                cout<<"#";

            }
            else
                cout<<".";
        }
        if(i % 2 !=0)
            swap(End, Start);

        cout<< endl;
    }

    return 0;
}
