/**
 * https://codeforces.com/contest/1990/submission/278440042
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Graph : vector<vector<int>> {
  int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

struct NodeInfo {
  int par, dep, siz, hei;
};

struct Subtree : vector<NodeInfo> {
  Subtree(const Graph &g, int s) : vector<NodeInfo>(g.size()) { dfs(g, s, s); }
  void dfs(const Graph &g, int u, int p, int d = 1) {
    auto &cur = (*this)[u] = {p, d, 1, 1};
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, v, u, d + 1);
        cur.siz += (*this)[v].siz;
        cur.hei = max(cur.hei, 1 + (*this)[v].hei);
      }
    }
  }
};

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

int simulate(Subtree &s, int &mole, int x) {
  int i = mole;
  while (i != 1 && i != x) {
    i = s[i].par;
  }
  if (i == x) {
    return true;
  }
  mole = s[mole].par;
  return false;
}

void solve(int t) {
  Int n;
#ifndef ONLINE_JUDGE
  Int mole;
#endif
  Graph g(n, n - 1);
  Subtree s(g, 1);
  int rem = 160;
  auto q = [&](int x) {
    assert(rem--);
    println('?', x);
#ifndef ONLINE_JUDGE
    return simulate(s, mole, x);
#else
    return Int();
#endif
  };
  vector<bool> vis(n + 1);
  auto f = [&](auto &self, int u, int p) -> void {
    vis[u] = true;
    for (auto &v : g[u]) {
      if (v != p) {
        self(self, v, u);
      }
    }
  };
  auto cmp = [&](int i, int j) { return s[i].dep > s[j].dep; };
  Iota ids(n, cmp, 1);
  for (int u : ids) {
    if (!vis[u]) {
      int v = u;
      for (int i = 0; i < (rem - 1) / 2 - 1 && v != 1; i++) {
        v = s[v].par;
      }
      if (q(v)) {
        int d = s[u].dep - s[v].dep + 1;
        for (int i = 0; i < d; i++) { // drive out of subtree
          if (q(u)) {
            v = u;
            break;
          }
          if (!q(v)) {
            v = s[s[v].par].par;
            break;
          }
        }
        println('!', v);
        return;
      }
      f(f, v, s[v].par); // cut subtree
    }
  }
  assert(false);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}