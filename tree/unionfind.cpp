#include <cstdio>
#include <iostream>
using namespace std;

void init(int *par, int N){
    for(int i=0; i<N; i++){
        par[i] = i;
    }
}

int root(int *par, int x){
    if(par[x] == x) return x;
    else return par[x] = root(par, par[x]);
}

bool same(int *par, int x, int y){
    return root(par, x) == root(par, y);
}

void unite(int *par, int x, int y){
    x = root(par, x);
    y = root(par, y);
    if(x == y) return;
    par[x] = y;
}

int main(void){
    int N, Q;
    cin >> N >> Q;
    //scanf("%d", &N);
    int par[N];
    init(par, N);
    for(int i=0; i<Q; i++){
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        if(p == 0){
            unite(par, a, b);
        }
        else{
            if (same(par, a, b)) {cout << "Yes" << endl;}
            else {cout << "No" << endl;}
        }
    }
    return 0;
}