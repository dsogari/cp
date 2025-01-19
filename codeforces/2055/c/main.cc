/**
 * https://codeforces.com/contest/2055/submission/300718760
 *
 * (c) 2025 Diego Sogari
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using I64 = Num<i64>;

template <typename T> struct Str : basic_string<T> {
  using basic_string<T>::basic_string;
  Str() { cin >> *this; }
};
using String = Str<char>;

template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    for (auto &row : *this) {
      row.resize(m);
    }
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int n, m;
  String path;
  Mat<I64> g(n, m);
  int i = 0, j = 0;
  for (auto &&c : path) {
    if (c == 'R') {
      for (int l = 0; l < n; l++) {
        if (l != i) {
          g[i][j] -= g[l][j];
        }
      }
      j++; // right
    } else {
      for (int l = 0; l < m; l++) {
        if (l != j) {
          g[i][j] -= g[i][l];
        }
      }
      i++; // down
    }
  }
  for (int l = 0; l < n; l++) {
    if (l != i) {
      g[i][j] -= g[l][j];
    }
  }
  for (auto &&row : g) {
    println(row);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
