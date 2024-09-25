/**
 * https://codeforces.com/contest/2013/submission/282953644
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
  int dfs(const Graph &g, int a, int b, int p) { // O(n)
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

void solve(int t) {
  Int n;
  Graph g(n, n - 1);
  Int u, v;
  assert(u == v);
  Path path(g, 1, u);
  vector<bool> vis(n + 1);
  for (auto &&x : path) {
    vis[x] = true;
  }
  auto f = [&](auto &self, int x, int p) -> int { // O(n)
    int ans = 0;
    for (auto &&y : g[x]) {
      if (y != p && !vis[y]) {
        ans = max(ans, self(self, y, x) + 1);
      }
    }
    return ans;
  };
  int m = path.size();
  vector<int> depth(m);
  for (int i = 0; i < m; i++) {
    depth[i] = f(f, path[i], path[i]);
  }
  string ans;
  for (int l = 0, r = m - 1, turn = 1; l <= r; turn = !turn) { // O(n)
    bool wins = true;
    for (int i = l + turn; i < r + turn && wins; i++) {
      wins = turn ? l + depth[l] > m - i - 1 + depth[i]
                  : i + depth[i] <= m - r - 1 + depth[r];
    }
    if (wins) {
      ans = turn ? "Alice" : "Bob";
      break;
    }
    turn ? l++ : r--;
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
