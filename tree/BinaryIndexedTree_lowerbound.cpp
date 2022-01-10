//k番目に小さな値を取得できるBIT

#include<bits/stdc++.h>

using namespace std;

const int bitsize = 200000;

int BIT[bitsize];

void add(int i, int x){
    for(; i < bitsize; i += (i&-i)){
        BIT[i] += x;
    }
}

int query(int i){
    int ret = 0;
    for(; i > 0; i -= (i&-i)) ret += BIT[i];
    return ret;
}

int lower_bound(int k){
    int pow2 = ceil(bitsize)-1;
    if(k <= 0) return 0;
    int x = 0;
    for (int k = (1 << pow2); k > 0; k >>= 1) {
        if (x + k <= bitsize && BIT[x + k] < k) {
            k -= BIT[x + k];
            x += k;
        }
    }
    return x + 1;
}

int main(void){
    for(int i = 1; i <= 3; i++) add(i, i);
    for(int i = 1; i <= 6; i++) cout << lower_bound(i) << endl;
    return 0;
}