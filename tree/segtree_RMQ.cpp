#include<bits/stdc++.h>

using namespace std;

int INF = INT_MAX;

struct SegmentTree{
private:
    int n; //セグ木のサイズ(=ノード数)
    vector<int> node;

public:
    //コンストラクタ: 元配列vを基にセグメント木を作成
    SegmentTree(){}
    SegmentTree(vector<int> v){
        int sz = v.size();
        int height = ceil(log2(sz)); // sz = 4 -> height = 2, sz = 5 -> height = 3
        n = pow(2, height); //セグ木における葉の数
        node.resize(2*n-1, INF); //RMQの場合,無効なノードはintの最大値で初期化

        //まずは最下段に値を入れる
        for(int i = 0; i < sz; i++) node[i+n-1] = v[i];
        //次に、根に登りつつ値を入れる
        for(int i = n-2; i >= 0; i--) node[i] = min(node[(i << 1) + 1], node[(i << 1) + 2]);
    }
    //値の取得クエリ [l, r)の最小値を取得
    int getmin(int a, int b, int k=0, int l=0, int r=-1){
        //最初の呼び出し時の対象区間は[0, n)
        if(r < 0) r = n;

        //[a, b)と[l, r)が交わらない -> INFを返す
        if(r <= a || b <= l) return INF;

        //[a, b)は[l, r)を完全に含む -> 現在のノードの値を返す
        if(a <= l && r <= b) return node[k];

        //[a, b)は[l, r)を一部含む -> 子について探索を行う
        int vl = getmin(a, b, (k << 1) + 1, l, (l+r)/2);
        int vr = getmin(a, b, (k << 1) + 2, (l+r)/2, r);
        return min(vl, vr);
    }

    //値の1点更新クエリ
    void update(int idx, int val){
        node[idx + (n-1)] = val;
        idx = idx + (n-1);
        while(idx > 0){
            idx = (idx % 2 == 0)? idx/2 - 1 : idx/2;
            node[idx] = min(node[(idx << 1)+1], node[(idx << 1)+2]);
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
    vector<int> A(n, INF);
    SegmentTree segtree(A);
    for(int i = 0; i < q; i++){
        int cmd, x, y; cin >> cmd >> x >> y;
        if(cmd == 0){
            segtree.update(x, y);
        }
        else{
            cout << segtree.getmin(x, y+1) << endl;
        }
        //segtree.show();
    }
    return 0;
}