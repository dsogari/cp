/**
 * https://codeforces.com/contest/1990/submission/278439686
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

struct Graph : vector<vector<int>> {
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1) {
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

int binsearch(auto &&f, int s, int e) {
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e;
}

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
  int rem = 300, limit = n / 300;
  auto q = [&](int x) {
    assert(rem--);
    println('?', x);
#ifndef ONLINE_JUDGE
    return simulate(s, mole, x);
#else
    return Int();
#endif
  };
  vector<int> path;
  auto f = [&](auto &self, int u, int p) -> void {
    path.push_back(u);
    vector<int> test;
    for (auto &&v : g[u]) {
      if (v != p) {
        if (s[v].hei + 1 == s[u].hei) {
          test.push_back(v);
        } else if (s[v].hei > limit && q(v)) {
          return self(self, v, u);
        }
      }
    }
    bool check = test.size() > 1;
    for (auto &v : test) {
      if (!check || (s[v].hei > limit && q(v))) {
        return self(self, v, u);
      }
    }
  };
  if (s[1].hei > limit) {
    f(f, 1, 1);
  }
  while (limit && !q(n)) {
    limit--;
  }
  int ans = n;
  if (!limit) {
    ans = 1;
    if (path.size()) {
      auto q2 = [&](int i) { return q(path[i]); };
      int i = binsearch(q2, 0, path.size() - 1);
      while (i > 0 && !q(path[i])) {
        i -= 2;
      }
      ans = path[max(0, i)];
    }
  }
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}