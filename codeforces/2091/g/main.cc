/**
 * https://codeforces.com/contest/2091/submission/328111806
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
  set<array<int, 2>> vis;
  q.push({0, k, 0});
  while (q.size()) {
    auto [l, k, m] = q.front();
    q.pop();
    if ((s - l) % k <= m) {
      return println(k);
    } else if (k == 2) {
      return println(1);
    }
    for (int i = 0; i <= m; i++, l++) {
      int ll = (l + 1) % (k - 1);
      if (vis.insert({ll, k - 2}).second) {
        int cnt = 2 * ((s - l) / k - 1) + (ll < l); // remainders mod k-2
        q.push({ll, k - 2, min(k - 2, cnt)});
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
