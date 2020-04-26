#include<bits/stdc++.h>

#define rep(i, N) for(int i = 0; i < N; i++)

using namespace std;
using ll = long long;

const int INF = INT_MAX;

struct LazySegmentTree{
private:
    int n;
    vector<int> node, lazy;
    vector<bool> lazyFlag;

public:
    LazySegmentTree(){}
    LazySegmentTree(vector<int> v){
        int sz = v.size();
        int height = ceil(log2(sz));
        n = pow(2, height);
        node.resize(2*n-1, 0);
        lazy.resize(2*n-1, INF);
        lazyFlag.resize(2*n-1, false);
        rep(i, sz) node[i+(n-1)] = v[i];
        for(int i = n-2; i >= 0; i--) node[i] = min(node[(i<<1)+1], node[(i<<1)+2]);
    }

    void lazyEval(int k, int l, int r){
        if(lazyFlag[k]){
            node[k] = lazy[k];
            if(r-l > 1){
                lazy[(k<<1) + 1] = lazy[k]; lazyFlag[(k<<1) + 1] = true;
                lazy[(k<<1) + 2] = lazy[k]; lazyFlag[(k<<1) + 2] = true;
            }
            lazyFlag[k] = false;
        }
    }

    int getmin(int a, int b, int k=0, int l=0, int r=-1){
        if(r < 0) r = n;

        lazyEval(k, l, r);
        if(b <= l || r <= a) return INF;
        else if(a <= l && r <= b) return node[k];
        else{
            int vl = getmin(a, b, (k<<1)+1, l, (l+r)/2);
            int vr = getmin(a, b, (k<<1)+2, (l+r)/2, r);
            return min(vl, vr);
        }
    }

    void update(int a, int b, int x, int k=0, int l=0, int r=-1){
        if(r < 0) r = n;

        lazyEval(k, l, r);
        if(b <= l || r <= a) return;
        else if(a <= l && r <= b){
            lazy[k] = x;
            lazyFlag[k] = true;
            lazyEval(k, l, r);
        }
        else{
            update(a, b, x, (k<<1)+1, l, (l+r)/2);
            update(a, b, x, (k<<1)+2, (l+r)/2, r);
            node[k] = min(node[(k<<1)+1], node[(k<<1)+2]);
        }
    }
};

int main(void){
    int n, q; cin >> n >> q;
    vector<int> A(n, INF);
    LazySegmentTree lst(A);
    rep(i, q){
        int cmd; cin >> cmd;
        if(cmd){
            int s, t; cin >> s >> t;
            cout << lst.getmin(s, t+1) << endl;
        }
        else{
            int s, t, x; cin >> s >> t >> x;
            lst.update(s, t+1, x);
        }
    }
}