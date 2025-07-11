/**
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  vector<array<i64, 2>> cost(n);
  i64 sum = 0;
  for (int i = 0; i < n + k; i++) { // O(n)
    if (i < n) {
      sum += a[i];
    }
    if (i >= k) {
      sum -= a[i - k];
      cost[i - k][1] = sum;
    }
    if (i < n - 1) {
      cost[i + 1][0] = sum;
    }
  }
  auto f = [&](int i) { return a[i] - cost[i][0] - cost[i][1]; };
  set<pair<i64, int>> s;
  for (int i = 0; i < n; i++) { // O(n*log n)
    s.emplace(f(i), i);
  }
  i64 ans = 0;
  Iota left(n, -1), right(n, 1);
  while (s.size()) { // O(n*log n)
    auto [x, i] = *s.begin();
    s.erase(s.begin());
    ans += a[i];
    int l = left[i], r = right[i];
    i64 lc = 0, rc = 0;
    for (int c = 0; c < k; c++) {
      if (l >= 0) {
        s.erase({f(l), l});
        lc = cost[l][0];
        l = left[l];
      }
      if (r < n) {
        s.erase({f(r), r});
        rc = cost[r][1];
        r = right[r];
      }
    }
    if (l >= 0) {
      right[l] = r;
    }
    if (r < n) {
      left[r] = l;
    }
    for (int c = 0; c < k; c++) {
      if (l >= 0) {
        s.erase({f(l), l});
        cost[l][1] = rc;
        s.emplace(f(l), l);
        rc += a[l];
        l = left[l];
      }
      if (r < n) {
        s.erase({f(r), r});
        cost[r][0] = lc;
        s.emplace(f(r), r);
        lc += a[r];
        r = right[r];
      }
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
