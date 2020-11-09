#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)
using namespace std;

typedef long long ll;

const int INF = 1 << 30;
const ll LLINF = 1LL << 62;

int mod = 1000000007;

int N;

int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //小さい要素から順にみて、右側で壁になってるとこと左側で壁になってるところを探す
  cin >> N;
  vector<int> A(N);
  vector<int> appear(N+1);
  set<int> idx; idx.insert(-1); idx.insert(N);
  rep(i, N){
    cin >> A[i];
    appear[A[i]] = i;
  }
  ll ans = 0;
  for(int i = 1; i <= N; i++){
    int pos = appear[i];
    //posより小なidx内の要素
    auto left = idx.lower_bound(pos);
    left--;
    auto right = idx.lower_bound(pos);
    ll lhs, rhs;
    if(left == idx.begin()) lhs = pos+1;
    else lhs = pos - *left;
    rhs = *right - pos;
    //cout << *left << " " << *right << endl;
    ans += lhs*rhs*i;

    idx.insert(pos);
  }
  cout << ans << endl;
  return 0;
}