/**
 * https://codeforces.com/contest/2091/submission/327922517
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

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
};
using Mint = Mod<int, 998244353>;

void update_dp(auto &cur, auto &next, auto &hold, int m, int d) { // O(m)
  Mint sum = 0;
  for (int j = 0, l = 0, r = 0, e = min(m, d + 1); j < m;) {
    if (r < m) {
      sum += cur[r++];
    }
    if (r >= e) {
      next[j] = hold[j] == 'X' ? sum : Mint();
      if (++j - l > d) {
        sum -= cur[l++];
      }
    }
  }
}

void solve(int t) {
  Int n, m, d;
  vector<Str> a(n);
  vector<Mint> dp1(m), dp2(m);
  for (int j = 0; j < m; j++) { // O(m)
    if (a[n - 1][j] == 'X') {
      dp1[j] = 1; // Base case: last row
    }
  }
  for (int i = n - 1; i >= 0; i--) { // O(n*m)
    update_dp(dp1, dp2, a[i], m, d);
    if (i > 0) {
      update_dp(dp2, dp1, a[i - 1], m, d - 1);
    }
  }
  auto ans = reduce(dp2.begin(), dp2.end()); // O(m)
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
