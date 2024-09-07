/**
 * https://codeforces.com/contest/2007/submission/280258167
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

struct Str : string {
  Str() { cin >> *this; }
};

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

void solve(int t) { // O(n)
  Int n;
  Graph g(n, n - 1);
  Str s;
  array<int, 3> leaves = {};
  int internal = 0;
  for (int u = 2; u <= n; u++) { // O(n)
    auto c = s[u - 1];
    if (g[u].size() == 1) {
      leaves[c == '?' ? 2 : c - '0']++;
    } else if (c == '?') {
      internal++;
    }
  }
  int ans = 0;
  if (s[0] == '?') {
    auto choice = leaves[0] < leaves[1]; // best value of root node
    ans = leaves[choice] + leaves[2] / 2;
    if (internal % 2) { // Iris can let Dora choose the root first
      ans = max(ans, leaves[!choice] + (leaves[2] + 1) / 2);
    }
  } else {
    ans = leaves[s[0] == '0'] + (leaves[2] + 1) / 2;
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
