/**
 * https://codeforces.com/contest/1998/submission/275668585
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

int binsearch(auto &&f, int s, int e) { // (s, e] O(log n)
  while (s < e) {
    auto m = s + (e - s + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
}

void solve(int t) {
  Int n, k;
  vector<Int> a(n), b(n);
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  Iota idx(n, cmp);
  int mid = n / 2 - 1, last = n - 1;
  i64 ans = a[idx[mid]] + a[idx[last]];
  for (; last >= 0 && !b[idx[last]]; last--)
    ;
  if (last >= 0) {
    ans = a[idx[mid + (last <= mid)]] + a[idx[last]] + i64(k); // use a[last]
    if (last < n - 1) {
      auto f = [&](int x) {
        int cnt = 0;
        for (int i = n - 2, available = k; i >= 0; i--) {
          if (a[idx[i]] >= x) {
            cnt++;
          } else if (b[idx[i]] && x - a[idx[i]] <= available) {
            cnt++;
            available -= x - a[idx[i]];
          }
        }
        return 2 * cnt > n - 1;
      };
      auto mid = binsearch(f, a[idx[0]], a[idx[n - 2]] + k);
      ans = max(ans, i64(mid) + a[idx[n - 1]]);
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
