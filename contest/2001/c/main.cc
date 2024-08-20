/**
 * https://codeforces.com/contest/2001/submission/277427855
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

#ifndef ONLINE_JUDGE
struct Graph : vector<vector<int>> {
  const int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

struct Path : vector<int> {
  Path(const Graph &g, int s, int e) { dfs(g, s, e, s); }
  int dfs(const Graph &g, int a, int b, int p) {
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

int simulate(Graph &g, int a, int b) {
  Path path(g, a, b);
  return path[(path.size() - 1) / 2];
}
#endif

void solve(int t) {
  Int n;
#ifndef ONLINE_JUDGE
  Graph g(n, n - 1);
#endif
  int rem = 15 * n;
  auto query = [&](int a, int b) {
    assert(rem--);
    println('?', a, b);
#ifndef ONLINE_JUDGE
    return simulate(g, a, b);
#else
    return Int();
#endif
  };
  vector<int> ans;
  auto f = [&](auto &self, int a, int b) { // O(log n)
    auto x = query(a, b);                  // middle node between a and b
    if (x == a || x == b) {
      ans.push_back(a);
      ans.push_back(b);
      return; // add edge between a and b
    }
    self(self, a, x); // binary search
  };
  for (int u = 1; u < n; u++) { // O(n*log n)
    f(f, u, n);
  }
  assert(ans.size() == 2 * (n - 1));
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
