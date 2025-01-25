/**
 * https://codeforces.com/contest/2060/submission/301916091
 *
 * Graph theory; DSU; DFS; greedy
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(1)
  int merge(int a, int b) { // O(1) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += exchange(siz[b], 0);
      par[b] = a;
    }
    return a;
  }
  int count() const { return siz.size() - ranges::count(siz, 0); } // O(n)
};

void solve(int t) {
  Int n, m1, m2;
  vector<array<Int, 2>> f(m1), g(m2);
  DSU dsu1(n + 1), dsu2(n + 1);
  for (auto [u, v] : g) {
    dsu2.merge(u, v);
  }
  int ans = 0;
  for (auto [u, v] : f) {
    if (dsu2.find(u) != dsu2.find(v)) {
      ans++;
    } else {
      dsu1.merge(u, v);
    }
  }
  ans += dsu1.count() - dsu2.count();
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
