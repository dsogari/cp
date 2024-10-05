/**
 * https://codeforces.com/contest/2000/submission/276316748
 *
 * (c) 2024 Diego Sogari
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void inclusion(int n, int m, int w, int h, auto &&f) {
  int rmx = min(h, n - h + 1); // window size vs number of windows
  int cmx = min(w, m - w + 1); // idem for columns
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int rc = min({rmx, i + 1, n - i}); // number of inclusions
      int cc = min({cmx, j + 1, m - j}); // idem for columns
      f(i, j, rc * cc);
    }
  }
}

void solve(int t) {
  Int n, m, k, w;
  vector<Int> a(w);
  vector<int> b;
  b.reserve(n * m);
  auto f = [&](int i, int j, int c) { b.push_back(c); };
  inclusion(n, m, k, k, f);
  ranges::sort(a, greater<int>{});
  ranges::sort(b, greater<int>{});
  i64 ans = 0;
  for (int i = 0; i < w; i++) {
    ans += i64(a[i]) * b[i];
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
