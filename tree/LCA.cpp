#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)
using namespace std;

typedef long long ll;

const int INF = 1 << 30;
const ll LLINF = 1LL << 62;

int mod = 1000000007;

const int NODE_MAX = 200000;

vector<int> nodes[NODE_MAX];
int parent[NODE_MAX];
int doubling_par[NODE_MAX][20];
int depth[NODE_MAX];

void initdoubling(){
    rep(i, NODE_MAX) rep(j, 20) doubling_par[i][j] = -1;
}

void dfs(int p, int s, int d){
    depth[s] = d;
    parent[s] = p;
    doubling_par[s][0] = p;

    for(auto to: nodes[s]){
        if(to == p) continue;
        dfs(s, to, d+1);
    }
}

void doubling(int N){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < N; j++){
            if(doubling_par[j][i] != -1 && doubling_par[doubling_par[j][i]][i] != -1){
                doubling_par[j][i+1] = doubling_par[doubling_par[j][i]][i];
            }
        }
    }
}

int LCA(int a, int b){
    map<int, int> two;
    rep(i, 20) two[1 << i] = i;
    if(depth[a] < depth[b]) swap(a, b);
    int need_climb = depth[a]-depth[b];
    for(; need_climb > 0; need_climb -= (need_climb & -need_climb)) 
        a = doubling_par[a][two[need_climb & -need_climb]];

    if(a == b) return a; //aがbの部分木の中に入っていたケース
    
    while(parent[a] != parent[b]){
        int ok = 0, ng = 20;
        int m = (ok+ng)/2;
        while(abs(ok-ng) > 1){
            if(doubling_par[a][m] != doubling_par[b][m]) ok = m;
            else ng = m;
            m = (ok+ng)/2;
        }
        a = doubling_par[a][ok];
        b = doubling_par[b][ok];
    }
    return parent[a];
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initdoubling();
    int N; cin >> N;
    /*
    rep(i, N-1){
        int a, b; cin >> a >> b;
        a--; b--;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }
    */
    rep(i, N){
        int k; cin >> k;
        rep(j, k){
            int a; cin >> a;
            nodes[i].push_back(a);
        }
    }
    dfs(-1, 0, 0);
    doubling(N);

    
    int Q; cin >> Q;
    rep(i, Q){
        int a, b; cin >> a >> b;
        //a--; b--;
        cout << LCA(a, b) << endl;
    }
    return 0;
}