/**
 * https://codeforces.com/contest/2106/submission/326609768
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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const span<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
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

int simulate(const Graph &g, auto &a, int root, int type, int k,
             const auto &nodes) {
  if (type == 1) {
    assert(k == nodes.size());
    int sum = 0;
    for (auto &&u : nodes) {
      Path path(g, root, u);
      for (auto &&v : path) {
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
  Int root;
  vector<Int> a(n);
#endif
  Graph g(n, n - 1);
  int rem = n + 200;
  auto query = [&](int type, int k, const auto &nodes) {
    assert(rem--);
    println('?', type, k, nodes);
#ifndef ONLINE_JUDGE
    return simulate(g, a, root, type, k, nodes);
#else
    return type == 1 ? Int() : Int(0);
#endif
  };
  vector<int> ans(n), siz(n + 1);
  vector<bool> vis(n + 1);
  auto get = [&](auto &get, int u, int p, int prev) -> void {
    auto sum = query(1, 1, vector{u});
    ans[u - 1] = sum - prev;
    for (auto &&v : g[u]) {
      if (v != p) {
        get(get, v, u, sum);
      }
    }
  };
  auto chk = [&](int u) { // O(log deg{u})
    int l = 0, r = g[u].size();
    while (l < r) {
      auto mid = (l + r + 1) / 2;
      auto nodes = span(&g[u][0], &g[u][mid]);
      auto sum1 = query(1, mid, nodes);
      query(2, u, vector<int>{});
      auto sum2 = query(1, mid, nodes);
      (abs(sum1 - sum2) == 2 * mid) ? l = mid : r = mid - 1;
    }
    return l < g[u].size() ? g[u][l] : u;
  };
  auto dfs = [&](auto &dfs, int u, int p, int n) -> int {
    siz[u] = 1;
    bool ok = true;
    for (auto &&v : g[u]) {
      if (v != p && !vis[v]) {
        auto s = dfs(dfs, v, u, n);
        if (s < 0) {
          return s;
        }
        siz[u] += s;
        ok = ok && s <= n / 2;
      }
    }
    if (ok && n - siz[u] <= n / 2) {
      vis[u] = true; // found centroid
      siz[p] = n - siz[u];
      auto v = chk(u); // next candidate
      if (v == u) {
        get(get, v, v, 0); // found root
      } else {
        dfs(dfs, v, u, siz[v]); // keep looking
      }
      return -1; // stop searching
    }
    return siz[u];
  };
  dfs(dfs, 1, 1, n);
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
