/**
 * https://codeforces.com/contest/2126/submission/329775293
 * https://codeforces.com/contest/2126/submission/329775391
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

using Int = Number<int>;

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

struct PaintDSU {
  vector<int> par;
  PaintDSU(int n) : par(n) { iota(par.begin(), par.end(), 0); }
  int find(int u) { return u == par[u] ? u : par[u] = find(par[u]); } // O(lg n)
  int merge(int u, int p) { return par[find(u)] = find(p); } // [u->p] O(lg n)
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  PaintDSU left(n), right(n);
  Iota idx(n, [&](int i, int j) { return a[i] > a[j]; });
  int ans = 0;
  auto f = [&](auto &dsu, int i, int inc, int end) {
    int p = dsu.find(i);
    ans = max(ans, a[i] - a[p]);
    if (p != end) {
      dsu.merge(p, p + inc);
    }
  };
  for (auto &&i : idx) {
    f(left, i, -1, 0);
    f(left, i, -1, 0);
    f(right, i, 1, n - 1);
    f(right, i, 1, n - 1);
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
