/**
 * (c) 2024 Diego Sogari
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
};

template <typename T> struct Min {
  T operator()(const T &lhs, const T &rhs) const { return min(lhs, rhs); }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  map<int, int> cnt;
  for (auto &&ai : a) { // O(n*log n)
    cnt[ai]++;
  }
  map<int, int> diff;
  int total = 0;
  for (auto &&[x, c] : cnt) { // O(n*log n)
    diff.emplace(x - total, 0);
    total += c;
  }
  int j = diff.size();
  for (auto &&[d, i] : diff) { // O(n)
    i = --j;
  }
  FenTree<int> fen(diff.size(), Min<int>{}, INT_MAX);
  total = 0;
  int ans = 0;
  for (auto &&[x, c] : cnt) { // O(n*log n)
    auto it = diff.lower_bound(x - total - c);
    assert(it != diff.end());
    auto y = fen.query(it->second);
    if (x - y > 1) {
      ans = max(ans, x - y);
    }
    fen.update(diff[x - total], x);
    total += c;
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
