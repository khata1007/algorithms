#include<bits/stdc++.h>

using namespace std;
using ll = long long int;

struct LazySegmentTree{
private:
    int n; //葉の数
    vector<ll> node, lazy; //普通のセグ木の配列と遅延配列

public:
    LazySegmentTree(){}
    LazySegmentTree(vector<ll> v){
        int sz = v.size();
        int height = ceil(log2(sz));
        n = pow(2, height);
        node.resize(2*n-1, 0);
        lazy.resize(2*n-1, 0);

        for(int i = 0; i < sz; i++) node[i+(n-1)] = v[i];
        for(int i = n-2; i >= 0; i--) node[i] = node[(i<<1) + 1] + node[(i<<1) + 2];
    }

    void eval(int k, int l, int r){
        if(lazy[k] != 0){
            node[k] += lazy[k];

            if(r-l > 1){
                lazy[(k<<1)+1] += lazy[k]/2;
                lazy[(k<<1)+2] += lazy[k]/2;
            }
            lazy[k] = 0;
        }
    }

    ll getsum(int a, int b, int k=0, int l=0, int r=-1){
        if(r < 0) r = n;
        //区間に交わりが無い -> 0を返す
        if(b <= l || r <= a) return 0;

        eval(k, l, r);
        //区間を全て覆う -> その区間和を返す
        if(a <= l && r <= b) return node[k];
        //区間に一部交わりがある
        else{
            ll vl = getsum(a, b, (k<<1)+1, l, (l+r)/2);
            ll vr = getsum(a, b, (k<<1)+2, (l+r)/2, r);
            return vl+vr;
        }
    }
    void update(int a, int b, ll v, int k=0, int l=0, int r=-1){
        if(r < 0) r = n;
        //[a,b)にvを足すクエリ
        eval(k, l, r);
        if(b <= l || r <= a) return;
        else if(a <= l && r <= b){
            lazy[k] += (r-l)*v;
            eval(k, l, r); //アクセス後はlazy[k]=0のはずなので、(r-l)*vを足した後に評価が必要
        }
        else{
            update(a, b, v, (k<<1)+1, l, (l+r)/2);
            update(a, b, v, (k<<1)+2, (l+r)/2, r);
            node[k] = node[(k<<1)+1] + node[(k<<1)+2];
        }
    }
};

int main(void){
    int n, q; cin >> n >> q;
    vector<ll> A(n, 0);
    LazySegmentTree lst(A);
    for(int i = 0; i < q; i++){
        int cmd; cin >> cmd;
        if(cmd == 0){
            int s, t; ll x; cin >> s >> t >> x;
            lst.update(s-1, t, x);
        }
        else{
            int s, t; cin >> s >> t;
            cout << lst.getsum(s-1, t) << endl;
        }
    }
}