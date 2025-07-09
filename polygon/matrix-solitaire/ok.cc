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
  vector<array<int, 2>> row(n * m / 2 + 1), b(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto &[r1, r2] = row[a[i][j]];
      r1 = exchange(r2, i);
    }
    b[i] = {0, m - 1}; // left and right indices
  }
  int cnt = 0;
  for (bool ok = true; ok;) {
    ok = false;
    for (int i = 0; i < n; i++) {
      bool ok2 = true;
      while (ok2) {
        ok2 = false;
        auto &[l, r] = b[i];
        if (l <= r) {
          auto x = a[i][l];
          auto i2 = row[x][i == row[x][0]];
          auto &[l2, r2] = b[i2];
          if (i2 != i && x == a[i2][l2]) {
            l++, l2++, cnt++;
            ok = ok2 = true;
          } else if (x == a[i2][r2]) {
            l++, r2--, cnt++;
            ok = ok2 = true;
          }
        }
        if (l <= r) {
          auto x = a[i][r];
          auto i2 = row[x][i == row[x][0]];
          auto &[l2, r2] = b[i2];
          if (i2 != i && x == a[i2][r2]) {
            r--, r2--, cnt++;
            ok = ok2 = true;
          } else if (x == a[i2][l2]) {
            r--, l2++, cnt++;
            ok = ok2 = true;
          }
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
