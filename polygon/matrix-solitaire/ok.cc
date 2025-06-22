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
  vector<array<int, 2>> row(n * m / 2 + 1);
  vector<deque<int>> b(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b[i].push_back(a[i][j]);
      auto &[r1, r2] = row[a[i][j]];
      r1 = exchange(r2, i);
    }
  }
  int cnt = 0;
  for (bool ok = true; ok;) {
    ok = false;
    for (int i = 0; i < n; i++) {
      if (b[i].size()) {
        auto x = b[i].front();
        auto r = row[x][i == row[x][0]];
        assert(b[r].size());
        if (i != r && x == b[r].front()) {
          b[i].pop_front();
          b[r].pop_front();
          ok = true;
          cnt++;
        } else if (x == b[r].back()) {
          b[i].pop_front();
          b[r].pop_back();
          ok = true;
          cnt++;
        }
      }
      if (b[i].size()) {
        auto x = b[i].back();
        auto r = row[x][i == row[x][0]];
        assert(b[r].size());
        if (i != r && x == b[r].back()) {
          b[i].pop_back();
          b[r].pop_back();
          ok = true;
          cnt++;
        } else if (x == b[r].front()) {
          b[i].pop_back();
          b[r].pop_front();
          ok = true;
          cnt++;
        }
      }
    }
  }
  auto ans = 2 * cnt == n * m ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
