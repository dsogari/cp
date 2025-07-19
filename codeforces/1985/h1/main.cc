/**
 * https://codeforces.com/contest/1985/submission/329768228
 *
 * (c) 2024 Diego Sogari
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

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

struct DSU {
  int cnt; // number of disjoint sets
  vector<int> par, siz;
  DSU(int n) : cnt(n), par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }
  int size(int u) { return siz[find(u)]; }                            // O(1)
  int find(int u) { return u == par[u] ? u : par[u] = find(par[u]); } // O(1)
  int merge(int u, int v) { // O(1) amortized
    u = find(u), v = find(v);
    if (u != v) {
      if (siz[u] < siz[v]) {
        swap(u, v);
      }
      siz[u] += exchange(siz[v], 0);
      par[v] = u;
      cnt--;
    }
    return u;
  }
};

void solve(int t) {
  Int n, m;
  vector<Str> g(n);
  DSU dsu(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '#') {
        auto v = i * m + j;
        if (i > 0 && g[i - 1][j] == '#') {
          dsu.merge(v, v - m);
        }
        if (j > 0 && g[i][j - 1] == '#') {
          dsu.merge(v, v - 1);
        }
      }
    }
  }
  int ans = 0;
  auto f = [&](int x, int y, auto &gg, auto &vv) {
    for (int i = 0; i < x; i++) {
      set<int> roots;
      int total = 0;
      for (int j = 0; j < y; j++) {
        if (gg(i, j) == '#') {
          roots.insert(dsu.find(vv(i, j)));
        } else {
          total++;
        }
        if (i > 0 && gg(i - 1, j) == '#') {
          roots.insert(dsu.find(vv(i - 1, j)));
        }
        if (i < x - 1 && gg(i + 1, j) == '#') {
          roots.insert(dsu.find(vv(i + 1, j)));
        }
      }
      for (auto r : roots) {
        total += dsu.siz[r];
      }
      ans = max(ans, total);
    }
  };
  auto g1 = [&](int i, int j) { return g[i][j]; };
  auto g2 = [&](int i, int j) { return g[j][i]; };
  auto v1 = [&](int i, int j) { return i * m + j; };
  auto v2 = [&](int i, int j) { return v1(j, i); };
  f(n, m, g1, v1);
  f(m, n, g2, v2);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
