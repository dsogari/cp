/**
 * https://codeforces.com/contest/2091/submission/328088238
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

void solve(int t) {
  Int s, k;
  queue<array<int, 3>> q;
  set<array<int, 3>> vis;
  q.push({0, k, 0});
  while (q.size()) {
    auto [l, k, m] = q.front();
    q.pop();
    if (k <= 1) {
      return println(1);
    }
    auto d = div(s - l, k);
    if (d.rem <= m) {
      return println(k);
    }
    for (int i = 0; i <= m; i++, l++) {
      auto d = div(s - l, k);
      int cnt = 2 * (d.quot - 1) + 1; // available remainders mod k-2
      int inc = (s - l - d.rem) / (k - 1) < k - 1; // whether cannot return to 0
      int inc2 = l + inc >= k - 1;                 // whether can go back past 0
      array<int, 3> next = {(l + inc) % (k - 1), k - 2, cnt - inc + inc2};
      if (vis.insert(next).second) {
        q.push(next);
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
