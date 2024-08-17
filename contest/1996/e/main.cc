/**
 * https://codeforces.com/contest/1996/submission/276990336
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T> struct Mod {
  constexpr static T _def = 1000000007; // 998244353;
  T x, m;
  operator T() const { return x; }
  void set(i64 y) { x = (y %= m) < 0 ? y + m : y; };
  Mod(i64 x = 0, T m = _def) : m(m) { set(x); }
  Mod operator+(auto y) const { return Mod(x, m) += y; }
  Mod operator-(auto y) const { return Mod(x, m) -= y; }
  Mod operator*(auto y) const { return Mod(x, m) *= y; }
  Mod operator/(auto y) const { return Mod(x, m) /= y; }
  Mod &operator+=(i64 y) { return set(x + y), *this; }
  Mod &operator-=(i64 y) { return set(x - y), *this; }
  Mod &operator*=(i64 y) { return set(x * y), *this; }
  Mod &operator/=(i64 y) { // O(log^2 m) / y and m must be coprime
    i64 u = 0, v = 1, d = m;
    while (y) {
      auto q = d / y;
      d -= q * y, swap(d, y); // (d, y) = (y, d - q * y)
      u -= q * v, swap(u, v); // (u, v) = (v, u - q * v)
    }
    assert(d == 1); // u*y == 1 (mod m)
    return operator*=(u);
  }
  Mod pow(auto y) const { // O(log y) / 0^0 -> 1
    Mod ans(1, m), base(x, m);
    for (; y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<int>;

void solve(int t) {
  Str s;
  int n = s.size();
  vector<int> sum(n + 1); // will hold values in the range [-n,n]
  for (int i = 0; i < n; i++) {
    sum[i + 1] += sum[i] + 2 * (s[i] - '0') - 1;
  }
  vector<vector<int>> idx_by_sum(2 * n + 1); // will hold 1-based indices
  for (int i = 0; i <= n; i++) {
    idx_by_sum[sum[i] + n].push_back(i);
  }
  Mint ans = 0;
  for (auto &idx : idx_by_sum) { // O(n) because there are at most n indices
    int m = idx.size();
    vector<Mint> cnt(m); // one less, because the first index doesn't count
    for (int i = 0; i < m - 1; i++) {
      cnt[i + 1] += cnt[i] + n - idx[i + 1] + 1;
    }
    for (int i = 0; i < m - 1; i++) {
      ans += (cnt.back() - cnt[i]) * (idx[i] + 1);
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
