#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)
using namespace std;

typedef long long ll;

const int INF = 1 << 30;
const ll LLINF = 1LL << 62;

int N;

ll bit[2][1000000];

void init(){
  rep(i, 2) rep(j, 1000000) bit[i][j] = 0;
}

void add(int l, int r, int val){
  for(int i = l; i <= N; i+= (i & -i)) bit[0][i] += -val * (l-1);
  for(int i = l; i <= N; i+= (i & -i)) bit[1][i] += val;
  for(int i = r+1; i <= N; i += (i & -i)) bit[0][i] += val*r;
  for(int i = r+1; i <= N; i += (i & -i)) bit[1][i] += -val;
}

ll sum(int i){
  vector<ll> ret(2);
  for(int idx = i; idx > 0; idx -= (idx & -idx)) ret[0] += bit[0][idx];
  for(int idx = i; idx > 0; idx -= (idx & -idx)) ret[1] += bit[1][idx];
  ret[1] *= i;
  return ret[0] + ret[1];
}

int mod = 1000000007;

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  int Q; cin >> N >> Q;
  vector<int> A(N+1); rep(i, N) cin >> A[i+1];
  vector<int> prev(N+1, 0);
  vector<pair<pair<int, int>, int>> query(Q);
  vector<ll> ans(Q);
  
  rep(i, Q){
    int l, r; cin >> l >> r;
    query[i] = make_pair(pair<int, int>(r, l), i);
  }
  sort(query.begin(), query.end());

  int idx = 1;
  rep(q, Q){
    int right = query[q].first.first, left = query[q].first.second;
    while(idx <= right){
      add(prev[A[idx]]+1, idx, 1);
      prev[A[idx]] = idx;
      idx++;
    }
    ans[query[q].second] = sum(left) - sum(left-1);
  }
  rep(i, Q) printf("%d\n", ans[i]);
  return 0;
}