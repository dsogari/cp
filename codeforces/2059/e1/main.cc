/**
 * https://codeforces.com/contest/2059/submission/304284030
 *
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, m;
  int nm = n * m;
  vector<Int> a(nm), b(nm);
  int i = 0;
  for (int j = 0; j < nm; j++) { // O(n*m)
    if (a[i] == b[j]) {
      i++;
    } else if (i / m == j / m) { // same row, different values
      i -= i % m;                // search from start of row
    }
  }
  println(nm - i);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
