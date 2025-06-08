/**
 * https://codeforces.com/contest/2117/submission/323554837
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Graph : vector<vector<int>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v] : edges) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v), (*this)[v].push_back(u); }
};

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
using Mint = Mod<int, 1000000007>;

struct Pow2 : vector<Mint> {
  Pow2(int n) : vector<Mint>(n + 1, 1) { // O(n)
    for (int i = 0; i < n; i++) {
      (*this)[i + 1] = (*this)[i] + (*this)[i];
    }
  }
};

void solve(int t) {
  Int n;
  Pow2 pow2(n);
  Graph g(n, n - 1);
  g[1].push_back(0); // dummy
  int leaves = ranges::count_if(g, [](auto &vv) { return vv.size() == 1; });
  if (leaves > 2) {
    return println(0);
  }
  if (leaves < 2) {
    return println(pow2[n]);
  }
  int len1 = 1, len2 = 0;
  for (int u = 1, p = 0; g[u].size() > 1; len1++) {
    if (g[u].size() > 2) {
      len2 = exchange(len1, 0); // bifurcation
    }
    auto v = g[u][0];
    if (v == p) {
      v = g[u][1];
    }
    p = exchange(u, v);
  }
  auto diff = abs(2 * len1 - n + len2);
  auto ans = pow2[len2 + diff] + pow2[len2 + max(0, diff - 1)];
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
