/**
    Problem Name: A. Even Odds 318 A
    Target : Big Data & time running
 **/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> odd;
    vector<int> even;

    long long int n = 0, k = 0;
    long long int counter = 1;
    long long int sizeN = 0;
    long long int i = 1;
    int sign = 1;

    cin>>n>>k;

    if(n % 2 == 0){
        sizeN = n / 2;

    }
    else{
        sizeN = (n+1) / 2;
    }

      if(k <= sizeN){
            if(k > sizeN/2){
                sign = -1;
                counter = sizeN;
                if(n %2 ==0)
                    i = n-1;
                else
                    i = n;
            }

      }
      else{
           if(k - sizeN > sizeN/2){
                sign = -1;
                counter = n;
                if(n %2 ==0)
                    i = n;
                else
                    i = n-1;
            }
            else{
                i = 2;
                counter = sizeN + 1;
            }
      }

        while(true){
           if(counter == k){
               cout<<i<<endl;
                break;
               }
               i = i + 2 * sign;
               counter = counter + 1*sign;
        }

    return 0;
}
