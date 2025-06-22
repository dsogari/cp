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

void solve(int t) {
  Int n, m;
  Mat<Int> a(n, m);
  vector<set<int>> rows(n), cols(m);
  vector<array<int, 2>> q, prev;
  for (int i = 0; i < n; i++) { // O(n*m*log(n*m))
    for (int j = 0; j < m; j++) {
      rows[i].insert(j);
      cols[j].insert(i);
    }
  }
  q.push_back({0, 0});
  rows[0].erase(0);
  cols[0].erase(0);
  for (int ans = 0; q.size(); ans++) { // O(n*m*log(n*m))
    swap(prev, q);
    for (auto [i, j] : prev) {
      if (i == n - 1 && j == m - 1) {
        return println(ans);
      }
      auto d = a[i][j];
      for (auto it1 = cols[j].lower_bound(i - d);
           it1 != cols[j].end() && *it1 <= i + d;) {
        q.push_back({*it1, j});
        rows[*it1].erase(j);
        it1 = cols[j].erase(it1);
      }
      for (auto it2 = rows[i].lower_bound(j - d);
           it2 != rows[i].end() && *it2 <= j + d;) {
        q.push_back({i, *it2});
        cols[*it2].erase(i);
        it2 = rows[i].erase(it2);
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
