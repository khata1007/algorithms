// 1-index Binary Indexed Tree //

#include<bits/stdc++.h>

using namespace std;

struct BinaryIndexedTree{
private:
    int n;
    vector<int> node;
public:
    BinaryIndexedTree(){}
    BinaryIndexedTree(int sz){
        n = sz+1;
        node.resize(n, 0);
    }

    void add(int a, int w){
        for(int x = a; x <= n; x += x & (-x)) node[x] += w;
    }

    int sum(int a){
        int ret = 0;
        for(int x = a; x > 0; x -= x & (-x)) ret += node[x];
        return ret;
    }
};

int main(){
    int N; cin >> N;
    int A[N]; for(int i = 0; i < N; i++) cin >> A[i];
    
    BinaryIndexedTree bit(N);
    for(int i = 0; i < N; i++) bit.add(i+1, A[i]);
    for(int i = 1; i <= N; i++) cout << bit.sum(i) << endl;

    return 0;
}