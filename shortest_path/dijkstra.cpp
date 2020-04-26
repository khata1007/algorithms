#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)

using namespace std;
using ll = long long;

//辺を記録するタイプのdijkstra

typedef struct Node{
    vector<int> edges_number;
    vector<int> edges_to;
    vector<int> edges_cost;

    int id;
    int from;

    bool done; //確定ノードかどうか
    int cost; //現時点での最小コスト
} Node;

void initNode(int N, Node *nodes, int *decide);
void dijkstra(int *use, int *decide, Node *nodes, int s, int N);

bool operator > (Node a, Node b){
    return a.cost > b.cost;
}
bool operator < (Node a, Node b){
    return a.cost < b.cost;
}

void initNode(int N, Node *nodes, int *decide){
    int bignum = 1000000000;
    rep(i, N){
        nodes[i].id = i;
        nodes[i].done = false;
        nodes[i].cost = bignum;
        decide[i] = 0;
    }
}

void dijkstra(int *use, int *decide, Node *nodes, int s, int N){
    //最短経路を求める
    priority_queue<Node, vector<Node>, greater<Node>> q;
    nodes[s].cost = 0;
    nodes[s].from = -1;
    q.push(nodes[s]); //63行目と順序を入れ替えるのはダメ(入れたものに対して変更するとヒープの整合性がね)
    while(!q.empty()){
        Node doneNode = q.top();
        q.pop();
        if(decide[doneNode.id] == 1) continue; //既に確定ノード -> continue

        doneNode.done = true; //確定ノードとする
        decide[doneNode.id] = 1;
        if(doneNode.cost != 0) use[doneNode.from] = 1; //使用した辺を記録
        int loop = doneNode.edges_to.size();
        rep(i, loop){
            int to = doneNode.edges_to[i];
            int c = doneNode.cost + doneNode.edges_cost[i];
            if(c < nodes[to].cost){
                nodes[to].cost = c;
                nodes[to].from = doneNode.edges_number[i];
                q.push(nodes[to]);
            }
        }
    }
}