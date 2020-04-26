#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)
#define PRIME_SIZE 1000001

typedef long long ll;
using namespace std;
int mod = 1000000007;

bool prime[PRIME_SIZE];
int min_factor[PRIME_SIZE];

void make_prime_list(){
    int loop = sqrt(PRIME_SIZE);
    for(int i = 2; i <= loop; i++){
        for(int j = (i << 1); j < PRIME_SIZE; j += i){
            prime[j] = false;
            if(min_factor[j] == j) min_factor[j] = i;
        }
    }
}

void init(){
    rep(i, PRIME_SIZE) prime[i] = true;
    prime[0] = prime[1] = false;
    rep(i, PRIME_SIZE) min_factor[i] = i;
    make_prime_list();
}

int main(void){
    init();
    rep(i, 10){
        cout << prime[i] << " ";
    }
    cout << endl;
    rep(i, 20) cout << min_factor[102+i] << " "; cout << endl;
    return 0;
}