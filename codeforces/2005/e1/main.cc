/**
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
  Int l, n, m;
  vector<Int> a(l);
  Mat<Int> b(n, m);
  unordered_set<int> valid;
  for (int i = 0; i < l && valid.insert(a[i]).second; i++)
    ;
  map<int, vector<array<int, 2>>> pos;
  auto f = [](auto &lhs, auto &rhs) { return lhs[1] > rhs[1]; };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (valid.contains(b[i][j])) {
        array<int, 2> cell{i, j};
        auto &cells = pos[b[i][j]];
        if (cells.size() && cells.back()[1] <= j) {
          auto k = ranges::lower_bound(cells, cell, f) - cells.begin();
          cells.resize(k);
        }
        cells.push_back(cell);
      }
    }
  }
  set<array<int, 2>> cur = {{-1, -1}};
  for (int k = 0; k < l; k++) {
    set<array<int, 2>> cur2;
    auto it = pos.find(a[k]);
    if (it != pos.end()) {
      for (auto &cell1 : cur) {
        bool ok = false;
        for (auto &cell2 : it->second) {
          if (cell2[0] > cell1[0] && cell2[1] > cell1[1]) {
            cur2.insert(cell2);
            ok |= true;
          }
        }
        if (!ok && k % 2) {
          println('T');
          return;
        }
      }
      if (cur2.empty()) {
        println(k % 2 ? 'T' : 'N');
        return;
      }
    }
    swap(cur, cur2);
  }
  println(l % 2 ? 'T' : 'N');
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
