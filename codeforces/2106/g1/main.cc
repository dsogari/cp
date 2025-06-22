/**
 * https://codeforces.com/contest/2106/submission/325497046
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

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

struct Path : vector<int> {
  Path(const Graph &g, int s, int e) { dfs(g, s, e, s); }
  bool dfs(const Graph &g, int a, int b, int p) { // O(n)
    push_back(a);
    if (a == b) {
      return true;
    }
    for (auto &v : g[a]) {
      if (v != p && dfs(g, v, b, a)) {
        return true;
      }
    }
    pop_back();
    return false;
  }
};

int simulate(const Graph &g, auto &a, int r, int type, int k,
             const vector<int> &nodes) {
  if (type == 1) {
    assert(k == nodes.size());
    int sum = 0;
    for (auto &&u : nodes) {
      for (auto &&v : Path(g, r, u)) {
        sum += a[v - 1];
      }
    }
    return sum;
  }
  assert(k >= 1 && k < g.size());
  a[k - 1] = -a[k - 1];
  return 0;
}

void solve(int t) {
  Int n;
#ifndef ONLINE_JUDGE
  Int r;
  vector<Int> a(n);
#endif
  Graph g(n, n - 1);
  int rem = n + 200;
  auto query = [&](int type, int k, const vector<int> &nodes) {
    assert(rem--);
    println('?', type, k, nodes);
#ifndef ONLINE_JUDGE
    return simulate(g, a, r, type, k, nodes);
#else
    return type == 1 ? Int() : Int(0);
#endif
  };
  vector<int> ans(n);
  auto s1 = query(1, 1, {1});
  if (abs(s1) == 1) { // 1 is root?
    ans[0] = s1;
    for (int u = 2; u <= n; u++) {
      ans[u - 1] = query(1, 1, {u}) - ans[0];
    }
  } else {
    if (s1 == 0) {
      query(2, 1, {}); // toggle a1 (temporarily)
      s1 = query(1, 1, {1});
    }
    ans[0] = s1 > 0 ? -1 : 1;
    query(2, 1, {}); // toggle a1
    for (int u = 2; u <= n; u++) {
      ans[u - 1] = query(1, 1, {u});
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
