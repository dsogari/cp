/**
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  FenTree(int n, T val = {}) : n(n), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans += nodes[i];
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] += val;
    }
  }
};

struct Node {
  int x;
  Node(int a = 0) : x(a) {}
  void operator+=(const Node &rhs) { x = min(x, rhs.x); }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  ranges::sort(a); // O(n*log n)
  a.push_back(INT_MAX);
  vector<array<int, 3>> vals;
  vector<int> diff;
  vals.reserve(n), diff.reserve(n);
  for (int i = 0, j = 0; i < n; i++) { // O(n)
    if (a[i + 1] > a[i]) {
      vals.push_back({a[i], i + 1 - j, a[i] - j});
      diff.push_back(a[i] - j);
      j = i + 1;
    }
  }
  ranges::sort(diff); // O(n*log n)
  int ans = 0, m = ranges::unique(diff).end() - diff.begin();
  FenTree<Node> fen(m, INT_MAX);
  for (auto [x, c, d] : vals) { // O(n*log n)
    auto i = ranges::lower_bound(diff, d - c) - diff.begin();
    auto j = ranges::lower_bound(diff, d) - diff.begin();
    auto y = fen.query(m - i - 1).x;
    if (y < INT_MAX && x - y > 1) {
      ans = max(ans, x - y);
    }
    fen.update(m - j - 1, x);
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
