#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string tobinary(long long int x, int n){
    string str = "";
    int r = 0, q = 0;
    char c ;
    while(x!=0){
        q = x/2;
        r = x - q*2;
        c = r+48;
        str = str + c;
        x = x/2;
    }
    reverse(str.begin(),str.end());
    for(int i = str.length(); i < n; i++){
        str = "0" + str ;
    }
    return str;
}


int main(){

    int n = 0 , m = 0 , k = 0;
    long long int x = 0;
    int counter = 0;
    string str = "";
    vector<string> players;


    cin >> n >> m >> k;

    for(int i =0; i <=m; ++i){
        cin>>x;
        str = tobinary(x,n);
        players.push_back(str);
        cout<<str<<endl;
    }

    char c = players[players.size()-1][k-1];
    for(int i =0; i <m; ++i){
        cout<<players[i][k-1]<<endl;
        if(c != players[i][k-1])
            counter++;
    }

    cout<<counter<<endl;
    return 0;
}
