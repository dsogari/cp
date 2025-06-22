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

template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    ranges::for_each(*this, [m](auto &row) { row.resize(m); });
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

struct SimpleDSU {
  vector<int> par;
  SimpleDSU(int n) : par(n) { iota(par.begin(), par.end(), 0); }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(lg n)
  int merge(int a, int b) { // O(lg n) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (a < b) {
        swap(a, b);
      }
      par[b] = a;
    }
    return a;
  }
};

void solve(int t) {
  Int n, m;
  Mat<Int> a(n, m);
  vector rows(n, SimpleDSU(m + 1)), cols(m, SimpleDSU(n + 1));
  vector<array<int, 2>> q, prev;
  auto push = [&](int i, int j) {
    q.push_back({i, j});
    rows[i].merge(j, j + 1);
    cols[j].merge(i, i + 1);
  };
  push(0, 0);
  for (int ans = 0; q.size(); ans++) { // O(n*m*log(n*m))
    swap(prev, q);
    for (auto [i, j] : prev) {
      if (i == n - 1 && j == m - 1) {
        return println(ans);
      }
      auto d = a[i][j];
      for (auto k = cols[j].find(max(0, i - d)); k < n && k <= i + d;
           k = cols[j].find(k)) {
        push(k, j);
      }
      for (auto k = rows[i].find(max(0, j - d)); k < m && k <= j + d;
           k = rows[i].find(k)) {
        push(i, k);
      }
    }
    prev.clear();
  }
  println(-1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
