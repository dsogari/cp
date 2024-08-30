/**
 * https://codeforces.com/contest/2003/submission/278757503
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

struct Digraph : vector<vector<int>> {
  const int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

constexpr int zero = 1, one = 2;

void solve(int t) { // O(n + m)
  Int n, m;
  Digraph g(n, m);
  vector<int> a(n);
  for (int l = 1, L = 0, R1 = 0, R2 = 0; l <= n; l++) { // O(n + m)
    if (g[l].empty()) {
      continue; // no interval starts here
    }
    int mn = n, mx = 0;
    for (auto &r : g[l]) {
      mn = min(mn, r);
      mx = max(mx, r);
    }
    if (l > R2) {
      a[l - 1] = zero;
      for (int j = mn; j <= mx; j++) {
        a[j - 1] = one;
      }
      L = l, R1 = mn, R2 = mx;
      continue; // non-overlapping interval
    }
    for (int j = L + 1; j <= l; j++) {
      if (a[j - 1] == one) {
        println(-1);
        return; // no interesting permutation exists
      }
      a[j - 1] = zero;
    }
    for (int j = mn; j < R1; j++) {
      a[j - 1] = one;
    }
    for (int j = R2 + 1; j <= mx; j++) {
      a[j - 1] = one;
    }
    L = l, R1 = min(R1, mn), R2 = max(R2, mx);
  }
  int ans = n * (n - 1) / 2, zeros = 0, ones = 0;
  for (int l = 0, r = n - 1; l <= r;) { // O(n)
    if (zeros < ones) {
      a[l] == zero ? zeros++ : ans -= zeros;
      l++;
    } else {
      a[r] == one ? ones++ : ans -= ones;
      r--;
    }
  }
  println(ans - zeros * ones);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
