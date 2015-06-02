#include <iostream>

using namespace std;

int main(){

    int n = 0;
    int p = 0;
    int minnum = 10000;
    int maxnum = 1;
    int counter = 0;
    cin>>n;

    for(int i = 0; i < n; ++i){
        cin>>p;
        if(i == 0){
            minnum = p;
            maxnum = p;

        }
        else{
            if(p < minnum){
                minnum = p;
                counter++;
            }
            else if(p > maxnum){
                maxnum = p;
                counter++;
            }

        }
    }

    cout<<counter<<endl;


    return 0;
}
