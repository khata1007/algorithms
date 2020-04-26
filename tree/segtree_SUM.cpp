#include<bits/stdc++.h>

using namespace std;

int INF = INT_MAX;

struct SegmentTree{
private:
    int n;
    vector<int> node;

public:
    SegmentTree(){}
    SegmentTree(vector<int> v){
        int sz = v.size();
        int height = ceil(log2(sz));

        n = pow(2, height);
        node.resize(2*n-1, 0);
        for(int i = 0; i < sz; i++){
            node[i + (n-1)] = v[i];
        }
        for(int i = n-2; i >= 0; i--){
            node[i] = node[(i << 1) + 1] + node[(i << 1) + 2];
        }
    }

    //区間和の取得
    int getsum(int a, int b, int k=0, int l=0, int r=-1){
        if(r < 0) r = n;

        //[l, r)は[a, b)と全く重ならない -> 0(単位元)を返す
        if(r <= a || b <= l) return 0;

        //[l, r)は[a, b)を完全に含む -> その区間の総和を返す
        if(a <= l && r <= b) return node[k];

        //[l, r)は[a, b)を一部含む -> 子を探索して左右の子の和を返す
        int vl = getsum(a, b, (k << 1) + 1, l, (l+r)/2);
        int vr = getsum(a, b, (k << 1) + 2, (l+r)/2, r);
        return vl + vr;
    }

    //1点の値を更新
    void update(int idx, int val){
        idx = idx + (n-1);
        node[idx] += val;
        while(idx > 0){
            idx = (idx % 2 == 0)? idx/2 - 1 : idx/2;
            node[idx] = node[(idx << 1) + 1] + node[(idx << 1) + 2];
        }
    }

    void show(){
        for(int i = 0; i < n; i++){
            cout << node[i + (n-1)] << " ";
        }
        cout << endl;
    }
};

int main(){
    int n, q; cin >> n >> q;
    vector<int> A(n, 0);
    SegmentTree segtree(A);
    //segtree.show();
    for(int i = 0; i < q; i++){
        int cmd, x, y; cin >> cmd >> x >> y;
        if(cmd == 0){
            x--;
            segtree.update(x, y);
        }
        else{
            x--; y--;
            cout << segtree.getsum(x, y+1) << endl;
        }
        //segtree.show();
    }
    return 0;
}