#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll pow(ll A, int n){
    if(n == 0) return 1;
    if(n&1) return A * pow(A, n-1);
    else{
        ll temp = pow(A, n/2);
        return temp*temp;
    }
}

int main(void){
    cout << pow(1, 1000000007) << endl;
    return 0;
}