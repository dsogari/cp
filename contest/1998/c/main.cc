/**
 * https://codeforces.com/contest/1993/submission/274347283
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n, k;
  vector<Int> a(n), b(n);
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  Iota idx(n, cmp);
  list<int> lst1, lst2;
  int mid = n / 2 - 1;
  for (int i = 0; i < n; i++) {
    if (b[idx[i]]) {
      (i <= mid ? lst1 : lst2).push_back(i);
    }
  }
  while (k > 0) {
    int j = mid == lst1.back() ? mid + 1 : mid;
    auto d1 = a[idx[j]] - a[idx[lst1.back()]];
    auto d2 = a[idx[n - 1]] - a[idx[lst2.back()]];
    if (d1 < d2) {
      auto inc = min<int>(k, d1 + 1);
      a[idx[lst1.back()]] += inc;
      swap(idx[j], idx[lst1.back()]);
      k -= inc;
    } else {
      k -= min<int>(k, d2 + 1);
    }
  }
  i64 ans = a[idx[n - 1]] + a[idx[mid]];
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
