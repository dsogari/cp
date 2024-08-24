/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u64 = uint64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Barret {
  u64 mod, div;
  Barret(u64 m) : mod(m), div(-1llu / m) {}
  operator u64() const { return mod; }
  i64 operator()(i64 x) const {
#ifdef __SIZEOF_INT128__
    x -= (x >= 0 ? __uint128_t(x) * div >> 64 : x / i64(mod)) * mod;
#else
    x %= i64(mod);
#endif
    return x < 0 ? x + mod : x < mod ? x : x - mod;
  }
};

template <typename T> struct Mod {
  inline static Barret mod = 1000000007; // 998244353;
  static i64 inv(i64 x, i64 m) {         // O(log^2 m) / x and m must be coprime
    return x < 0 ? inv(x % m + m, m) : x > 1 ? m - inv(m % x, x) * m / x : 1;
  } // https://codeforces.com/blog/entry/23365
  T x;
  Mod(i64 y = 0) { x = mod(y); }
  operator T() const { return x; }
  Mod operator+(auto y) const { return Mod(x) += y; }
  Mod operator-(auto y) const { return Mod(x) -= y; }
  Mod operator*(auto y) const { return Mod(x) *= y; }
  Mod operator/(auto y) const { return Mod(x) /= y; }
  Mod &operator+=(i64 y) { return x = mod(x + y), *this; }
  Mod &operator-=(i64 y) { return x = mod(x - y), *this; }
  Mod &operator*=(i64 y) { return x = mod(x * y), *this; }
  Mod &operator/=(i64 y) { return *this *= inv(y, mod); }
  Mod pow(auto y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1), base(y < 0 ? inv(x, mod) : x);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<int>;

void solve(int t) {
  Int n, k, p;
  Mint::mod = int(p);
  vector<Mint> gt(k + 1, 1), lt(k + 1, 1), gt2(k + 1, 1), sum(k + 1);
  gt[0] = gt2[0] = 0;
  for (int i = 1; i < n; i++) {   // O(n*k^2)
    for (int j = k; j > 0; j--) { // work backwards to reuse the dp vector
      sum[j] = gt2[j];
      for (int x = 1; x < j && x + j <= k; x++) {
        sum[j] += lt[x] * (gt2[j] - sum[x]) + gt[x] * sum[x - 1];
      }
      for (int x = 1; x < j - x; x++) { // deterministic choices
        gt[j] += lt[x] * gt[j - x];
        lt[j] += lt[x] * lt[j - x];
        gt2[j] += lt[x] * (gt2[j - x] - sum[x]) + gt[x] * sum[x - 1];
      }
      gt[j] *= 2; // adjustment due to the tree symmetry
      lt[j] *= 2;
      gt2[j] *= 2;
      sum[j] *= 2;
      if (j % 2 == 0) { // non-deterministic choices
        lt[j] += lt[j / 2] * lt[j / 2];
      }
    }
    for (int j = 1; j <= k; j++) { // accumulate to get the actual values
      gt[j] += gt[j - 1];
      lt[j] += lt[j - 1];
      gt2[j] += gt2[j - 1];
      sum[j] += sum[j - 1];
    }
    assert(sum[k] == gt2[k]);
  }
  println(gt2[k]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
