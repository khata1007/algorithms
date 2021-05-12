#include<bits/stdc++.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < n; i++)

template <class T>
class SegTree{
    int n;
    vector<T> data;
    T def; //初期値,単位元
    function<T(T, T)> operation; //区間クエリで使う処理
    function<T(T, T)> update; //1点更新で使う処理

    //区間[a,b)の総和
    T _query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return def; //交差しない時
        if(a <= l && r <= b) return data[k]; //[l,r)が完全に含まれるとき
        else{
            T c1 = _query(a, b, (k << 1)+1, l, (l+r)/2);
            T c2 = _query(a, b, (k << 1)+2, (l+r)/2, r);
            return operation(c1, c2);
        }
    }

  public:
    // _n:必要サイズ _def:初期値かつ単位元 _operation:クエリ関数
    // _update:更新関数
    SegTree(size_t _n, T _def, function<T(T, T)> _operation, function<T(T, T)> _update)
        : def(_def), operation(_operation), update(_update){
        n = 1;
        while(n < _n){
            n *= 2;
        }
        int datasize = 2*n-1;
        data = vector<T>(datasize);
        for(int i = 0; i < (int) vec.size(); i++) data[i+n-1] = vec[i];
        for(int i = n-2; i >= 0; i--) data[i] = operation(data[(i << 1) + 1], data[(i << 1) + 2]);
    }

    //場所i(0-idx)の値をxで更新
    void change(int i, T x){
        i += n-1;
        data[i] = update(data[i], x);
        while(i > 0){
            i = (i-1)/2;
            data[i] = operation(data[(i<<1) + 1], data[(i<<1) + 2]);
        }
    }

    T query(int a, int b){
        return _query(a, b, 0, 0, n);
    }

    T operator[](int i){
        return data[i+n-1];
    }
};
/* RMQデバッグ用
int main(void){
    int N, Q; cin >> N >> Q;
    SegTree<long long> st(N, (1LL << 31)-1,
                        [](long long a, long long b){return min(a, b);},
                        [](long long a, long long b){return b;});
    
    rep(q, Q){
        int c, x, y; cin >> c >> x >> y;
        if(c == 0){
            st.change(x, y);
        }
        else{
            cout << st.query(x, y+1) << endl;
        }
    }
    cout << st[0] << endl;

    return 0;
}
*/