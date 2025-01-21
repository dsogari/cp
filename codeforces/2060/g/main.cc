/**
 * https://codeforces.com/contest/2060/submission/302296907
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n;
  vector<Int> a(n), b(n);
  auto cmp = [&](int i, int j) { return min(a[i], b[i]) < min(a[j], b[j]); };
  Iota idx(n, cmp); // O(n*log n)
  int flips = 0, extra = n % 2;
  for (int i = 0, prevmax = 0; i < n; i++) { // O(n)
    auto [mn, mx] = minmax(a[idx[i]], b[idx[i]]);
    if (prevmax > mx) {
      println("NO");
      return;
    }
    flips += a[idx[i]] > b[idx[i]];
    extra |= prevmax < mn && i % 2;
    prevmax = mx;
  }
  auto ans = flips % 2 == 0 || extra ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
