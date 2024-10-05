/**
 * https://codeforces.com/contest/2003/submission/278195020
 *
 * (c) 2024 Diego Sogari
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Digraph : vector<vector<int>> {
  const int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

auto apsum(auto a, auto b, auto n) { return n * (a + b) / 2; }

void solve(int t) { // O(sum(li))
  Int n, m;
  vector<vector<Int>> a(n);
  Digraph g(0);
  int best1 = 0, best2 = 0;
  for (auto &ai : a) { // O(sum(li))
    Int li;
    ai.resize(li);
    g.resize(max<int>(g.size(), li + 2));
    vector<bool> vis(li + 2);
    for (auto &aai : ai) { // O(li)
      if (aai < li + 2) {
        vis[aai] = true;
      }
    }
    for (int j = 0, c = 0, u; j < li + 2 && c < 2; j++) { // O(li)
      if (!vis[j]) {
        if (c++) {
          g.add(u, j);
          best1 = max(best1, j);
        } else {
          u = j;
          best2 = max(best2, j);
        }
      }
    }
  }
  vector<int> dp(g.size());
  for (int u = best1; u >= 0; u--) { // O(max(li))
    dp[u] = u;
    for (auto &v : g[u]) {
      dp[u] = max(dp[u], dp[v]);
    }
    if (g[u].size() > 1) {
      best2 = max(best2, dp[u]);
    }
  }
  auto [mn, mx] = minmax<i64>({m, best1});
  i64 ans = apsum(best1 + 1, mx, mx - best1);
  for (int i = 0; i <= mn; i++) { // O(min(m,max(li)))
    ans += max({i, best2, dp[i]});
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
