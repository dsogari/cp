/**
 * https://codeforces.com/contest/2007/submission/280761796
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

template <typename T> struct Sparse {
  int k, n;
  vector<vector<T>> nodes;
  function<T(const T &, const T &)> f;
  Sparse(int n, auto &&f)
      : k(bit_width(unsigned(n))), n(n), f(f), nodes(k, vector<T>(n)) {}
  T &operator[](int i) { return nodes[0][i]; } // O(1)
  void build() {                               // O(n*log n)
    for (int i = 0; i < k - 1; i++) {
      for (int j = 0; j + (1 << i) < n; j++) {
        nodes[i + 1][j] = f(nodes[i][j], nodes[i][j + (1 << i)]);
      }
    }
  }
  T query(int l, int r) const { // [l, r] O(log n)
    _check(l, r);
    T ans = {};
    for (int i = k - 1; i >= 0; i--) {
      if ((1 << i) <= r - l + 1) {
        ans = f(ans, nodes[i][l]);
        l += 1 << i;
      }
    }
    return ans;
  }
  T min(int l, int r) const { // [l, r] O(1)
    _check(l, r);
    int i = bit_width(unsigned(r - l + 1)) - 1;
    return f(nodes[i][l], nodes[i][r - (1 << i) + 1]);
  }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

void solve(int t) { // O(n*log n*log V)
  Int n;
  vector<Int> a(n);
  Sparse<int> sparse(n, gcd<int, int>);
  for (int i = 1; i < n; i++) { // O(n)
    sparse[i] = abs(a[i] - a[i - 1]);
  }
  sparse.build(); // O(n*log n*log V)
  vector<int> c(n + 1);
  for (int l = 1, r = 1; l < n; l++) { // O(n*log V)
    if (!sparse[l]) {
      continue;
    }
    r = max(r, l);
    while (r < n && !has_single_bit(unsigned(sparse.query(l, r)))) {
      r++;
    }
    c[l] = n - r;
  }
  i64 ans = n;
  for (int i = n - 1; i > 0; i--) {
    if (!sparse[i]) {
      c[i] = c[i + 1] + 1;
    }
    ans += c[i];
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
