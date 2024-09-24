/**
 * https://codeforces.com/contest/2014/submission/282821307
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

void solve(int t) {
  Int n, m, k;
  vector<array<Int, 2>> a(n);
  vector<array<int, 2>> milk;
  a.push_back({a.back()[0] + k, 0});
  int ans = 0, day = 1;
  for (auto [d, c] : a) { // O(n)
    i64 total = 0, mx = i64(d - day) * m;
    while (total < mx && milk.size()) {
      auto &[e, l] = milk.back();
      i64 diff = e - day - total / m;
      if (diff > 0) {
        auto drink = min<i64>({l, mx - total, diff * m});
        total += drink;
        l -= drink;
        if (!l || total < mx) {
          milk.pop_back();
        }
      } else {
        milk.clear();
      }
    }
    ans += total / m;
    milk.push_back({d + k, c});
    day = d;
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
