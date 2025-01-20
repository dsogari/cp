/**
 * https://codeforces.com/contest/2060/submission/302153370
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t; // available on 64-bit targets

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T, auto M> struct Mod {
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  static V inv(V x, V m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  make_unsigned_t<T> x;
  Mod() : x(0) {}
  Mod(auto y) : x(y % M) { x >= M ? x += M : x; }
  operator T() const { return x; }
  Mod operator-() const { return Mod() -= *this; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return (x += rhs.x) >= M ? x -= M : x, *this; }
  Mod &operator-=(Mod rhs) { return (x -= rhs.x) >= M ? x += M : x, *this; }
  Mod &operator*=(Mod rhs) { return x = x * V(rhs.x) % M, *this; }
  Mod &operator/=(Mod rhs) { return x = x * inv(rhs.x, M) % M, *this; }
  Mod pow(auto y) const { // O(log y) | 0^(-inf,0] -> 1
    Mod ans(1), base(*this);
    for (auto e = y < 0 ? ~y + u128(1) : +y; e; e >>= 1, base *= base) {
      e & 1 ? ans *= base : ans;
    }
    return y < 0 ? Mod(1) /= ans : ans;
  }
};
using Mint = Mod<int, 998244353>;

void solve(int t) {
  Int k, n;
  auto logk = min<int>(n, bit_width<unsigned>(k)); // max number of factors
  vector<Mint> ans(k), inv(logk + 2, 1), comb(logk + 2, 1);
  for (int l = 1; l <= logk + 1; l++) {
    inv[l] /= l;
    comb[l] = comb[l - 1] * (n + 2 - l) * inv[l]; // hockey-stick identity
  }
  vector<vector<Mint>> memo(k + 1, vector<Mint>(logk + 1));
  auto f = [&](auto &self, int i, int x, int l, int cnt, Mint prod) -> void {
    prod *= inv[cnt] * l;
    memo[x][l] += prod;
    if (l < logk) {
      for (int j = i; u64(x) * j <= k; j++) {
        self(self, j, x * j, l + 1, j == i ? cnt + 1 : 1, prod);
      }
    }
  };
  ans[0] = n;
  for (int i = 2; i <= k; i++) { // O(k*log^2 k)
    f(f, i, i, 1, 1, 1);
    for (int l = 1; l <= logk; l++) {
      ans[i - 1] += memo[i][l] * comb[l + 1];
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
