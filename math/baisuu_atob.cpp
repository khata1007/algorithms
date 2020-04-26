#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll baisuu_atob(ll a, ll b, ll x){
    if(a % x > 0) a += x - (a % x);
    b -= a;
    if(b < 0) return 0;
    else return b/x + 1;
}
int main(void){
    ll a, b, x; cin >> a >> b >> x;
    cout << baisuu_atob(a, b, x) << endl;
    return 0;
}