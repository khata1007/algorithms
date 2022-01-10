#include <bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < n; i++)
using namespace std;

typedef long long ll;
typedef pair<pair<long long, long long>, pair<long long, long long>> resLE2_t;

const int INF = 1 << 30;
const ll LLINF = 1LL << 60;

int mod = 1000000007;

inline long long supermod(long long a, long long m) {
    return (a % m + m) % m;
}

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

    pair<pair<long long, long long>, pair<long long, long long>> solve(long long c){ //_a*x + _b*y = c なる 解 (x, y) をリターン
        long long p, q;
        long long d = _extGCD(_a, _b, p, q); //_a*p + _b*q = d = gcd(_a, _b)
        assert(_a*p + _b*q == d);
        if(c%d != 0) return make_pair(make_pair(-LLINF, -LLINF), make_pair(-LLINF, -LLINF));
        p *= c/d, q *= c/d;
        return make_pair(make_pair(p, _b/d), make_pair(q, _a/d)); 
    }
    pair<long long, long long> ChineseRem(long long b1, long long m1, long long b2, long long m2){
        long long p, q;
        long long d = _extGCD(m1, m2, p, q); // p is inv of m1/d (mod. m2/d)
        if ((b2 - b1) % d != 0) return make_pair(0, -1);
        long long m = m1 * (m2/d); // lcm of (m1, m2)
        long long tmp = (b2 - b1) / d * p % (m2/d);
        long long r = supermod(b1 + m1 * tmp, m);
        return make_pair(r, m);
    }
};

pair<long long, long long> geqzero_range(ll n, ll a){
    //n+ka >= 0 になる k の range: ka >= -n
    assert(a != 0);
    if(a > 0) return pair<long long, long long>(-(n/a), LLINF);
    else return pair<long long, long long>(-LLINF, n/(-a));
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, c;
    cout << "input a, b, c (ax + by = c)" << endl;
    cin >> a >> b >> c;
    LE2 le2(a, b);
    resLE2_t res = le2.solve(c);
    cout << "(x, y) = (" << res.first.first << " + " << res.first.second << "Z, " << res.second.first << " - " << res.second.second << "Z)" << " is solution of ax + by = c" << endl;
    return 0;
}