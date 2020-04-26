#include<bits/stdc++.h>
#define INF 1000000000000000

using namespace std;
using ll = long long;


typedef pair<ll, int> P; //コスト, 頂点の番号
struct edge{
    int to;
    ll cost;
};

int N; //ノード数
vector<edge> G[100000]; //各ノードの持つ辺
ll d[100000]; //ノードの現時点での最小コスト

void dijkstra(int s){
    priority_queue<P, vector<P>, greater<P>> pq;
    fill(d, d+N, INF);
    pq.push(P(0, s));
    d[s] = 0;

    while(!pq.empty()){
        P p = pq.top();
        pq.pop();
        ll now = p.second;
        if(p.first > d[now]) continue; //取り出した値が既に更新した値より大きいことがある

        for(int i = 0; i < G[now].size(); i++){
            edge e = G[now][i];
            if(d[e.to] > d[now] + e.cost){
                d[e.to] = d[now] + e.cost;
                pq.push(P(d[e.to], e.to));
            }
        }
    }
}

int main(void){
    int E, r; cin >> N >> E >> r;
    int temp; cin >> temp;
    for(int i = 0; i < E; i++){
        int a, b; ll c, d;
        cin >> a >> b >> c >> d;
        edge e; e.to = b; e.cost = c;
        G[a].push_back(e);
        e.to = a;
        G[b].push_back(e);
    }
    dijkstra(r);
    /*
    for(int i = 0; i < N; i++){
        if(d[i] != INF) cout << d[i] << endl;
        else cout << "INF" << endl;
    }
    */
}

