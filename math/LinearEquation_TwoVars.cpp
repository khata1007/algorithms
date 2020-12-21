#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)
using namespace std;

typedef long long ll;
typedef pair<pair<long long, long long>, pair<long long, long long>> resLE2_t;

const int INF = 1 << 30;
const ll LLINF = 1LL << 60;

int mod = 1000000007;

struct LE2{
private:
    long long _a, _b;
    long long _extGCD(long long a, long long b, long long &x, long long &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        long long d = _extGCD(b, a%b, y, x);
        y -= a/b * x;
        return d;
    }

public:
    LE2(long long  ta, long long tb){
        _a = ta; _b = tb;
    }

    pair<pair<long long, long long>, pair<long long, long long>> extGCD(long long c){
        long long g = __gcd(_a, _b);
        if(c%g > 0) return make_pair(make_pair(-LLINF, -LLINF), make_pair(-LLINF, -LLINF));

        long long x, y;
        _extGCD(_a/g, _b/g, x, y); //_a*x + _b*y = 1が成り立つ
        x *= c/g, y *= c/g;
        return make_pair(make_pair(x, _b/g), make_pair(y, _a/g)); 
    }
};

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, c;
    cout << "input a, b, c (ax + by = c)" << endl;
    cin >> a >> b >> c;
    LE2 le2(a, b);
    resLE2_t res = le2.extGCD(c);
    cout << "(x, y) = (" << res.first.first << " + " << res.first.second << "Z, " << res.second.first << " - " << res.second.second << "Z)" << " is solution of ax + by = c" << endl;
    return 0;
}