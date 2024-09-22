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

void solve(int t) {
  Int n, m, k;
  vector<array<Int, 2>> da(n);
  map<int, vector<array<int, 2>>> days;
  int mx = 0;
  for (auto &&[d, a] : da) { // O(n*log n)
    auto expiry = d + k - 1;
    days[d].push_back({a, expiry});
    mx = max(mx, expiry);
  }
  int ans = 0;
  for (auto it = days.begin(); it != days.end(); it = days.erase(it)) {
    auto &[today, pints] = *it;
    auto next = days.find(today + 1);
    int total = 0;
    for (auto [c, e] : pints) {
      auto drink = min(c, m - total);
      total += drink;
      c -= drink;
      if (c) {
        if (e <= today) {
          break;
        }
        if (next == days.end()) {
          next = days.insert({today + 1, {}}).first;
        }
        next->second.push_back({c, e});
      }
    }
    ans += total == m;
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
