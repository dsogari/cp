/**
 * https://codeforces.com/contest/2013/submission/282195102
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
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), e(m) {
    for (auto &[u, v] : e) {
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

int binsearch(auto &&f, int s, int e) { // (s, e] O(log n)
  for (int inc = s < e ? 1 : -1; s != e;) {
    auto m = s + (e - s + inc) / 2; // |e - s| < 2^31-1
    f(m) ? s = m : e = m - inc;
  }
  return e; // last such that f is true
}

void solve(int t) {
  Int n;
  Graph g(n, n - 1);
  Int u, v;
  vector<bool> vis(n + 1);
  auto f = [&](auto &self, int a, int b, bool turn) -> bool {
    bool ans = turn;
    for (auto &&v : g[turn ? b : a]) {
      if (!vis[v]) {
        vis[v] = true;
        auto alicewins = self(self, turn ? a : v, turn ? v : b, !turn);
        vis[v] = false;
        if (turn ^ alicewins) {
          ans = !ans;
          break;
        }
      }
    }
    return ans;
  };
  vis[1] = true;
  Path path(g, u, v);
  int m = path.size();
  auto f2 = [&](int i) {
    vis[path[i]] = true;
    auto alicewins = f(f, 1, path[i], 0);
    vis[path[i]] = false;
    return !alicewins;
  };
  auto f3 = [&](int l, int r) {
    auto mid = (l + r) / 2;
    auto last1 = binsearch(f2, l - 1, mid - 1);
    auto last2 = binsearch(f2, r, mid);
    for (int i = l; i < r; i++) {
      auto ans = i > last1 && i < last2 ? "Alice" : "Bob";
      println(ans);
    }
  };
  Path path2(g, u, 1);
  int k = 0;
  for (; k < m && k < path2.size() && path[k] == path2[k]; k++)
    ;
  if (k == 1 || k == path.size()) { // u or v is the entrypoint
    f3(0, m);
  } else { // k - 1 is the entrypoint
    f3(0, k);
    f3(k, m);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
