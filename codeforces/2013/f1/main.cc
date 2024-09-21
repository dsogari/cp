/**
 * https://codeforces.com/contest/2013/submission/282194464
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

void solve(int t) {
  Int n;
  Graph g(n, n - 1);
  Int u, v;
  assert(u == v);
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
  vis[1] = vis[u] = true;
  auto ans = f(f, 1, u, 0) ? "Alice" : "Bob";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
