#include<bits/stdc++.h>

using namespace std;

template <int Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  int a;

  constexpr modint(int x = 0) noexcept : a(x % Modulus){
      if(a < 0) a += Modulus;
  }
  constexpr int &value() noexcept { return a; }
  constexpr const int &value() const noexcept { return a; }

  constexpr modint operator+(const modint rhs) const noexcept { return modint(*this) += rhs;}
  constexpr modint operator-(const modint rhs) const noexcept { return modint(*this) -= rhs;}
  constexpr modint operator*(const modint rhs) const noexcept { return modint(*this) *= rhs;}
  constexpr modint operator/(const modint rhs) const noexcept { return modint(*this) /= rhs;}
  //increment, decrement
  constexpr modint &operator++() noexcept {a++; if(a >= Modulus) a -= Modulus; return *this;}
  constexpr modint &operator--() noexcept {a--; if(a < 0) a += Modulus; return *this;}

  //calc inverse
  constexpr modint operator~() noexcept {return modint(1) / *this;}

  //interpret -1 as (modulus - 1)
  constexpr modint operator-() noexcept{ return modint(-a);}
  
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = (int) (1LL * a * rhs.a % Modulus);
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    int exp = Modulus - 2;
    while (exp) {
      if (exp & 1) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp >>= 1;
    }
    return *this;
  }

  //judge equal or not equal
  constexpr bool operator ==(const modint& rhs){return this->a == rhs.a;}
  constexpr bool operator !=(const modint& rhs){return this->a != rhs.a;}

  modint pow(int64_t n) const {
    modint ret(1), mul(a);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend constexpr ostream& operator << (ostream &os, const modint& x) noexcept {
    return os << x.a;
  }
  
};

const int MAX = 510000;
const int MOD = 1000000007;

using mint = modint<MOD>;

mint fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * mint(i);
        inv[i] = mint(MOD) - inv[MOD%i] * mint(MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

// 二項係数計算
mint COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k]);
}

int main(void){
    COMinit();
    cout << COM(30, 15) << endl;
    return 0;
}