/**
 * https://codeforces.com/contest/2091/submission/328128964
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
  map<int, int> dp1 = {{0, 0}}, dp2;
  for (; k > 1; k -= 2) { // O(k^2*log k)
    while (dp1.size()) {
      auto [l, m] = *dp1.begin();
      dp1.erase(dp1.begin());
      if ((s - l) % k <= m) {
        return println(k);
      }
      for (int i = 0; i <= m; i++) {
        int ll = (l + i + 1) % (k - 1);
        if (!dp2.contains(ll)) {
          int cnt = 2 * ((s - l - i) / k - 1); // remainders mod k-2
          dp2.emplace(ll, min(k - 2, cnt + (ll < l + i + 1)));
        }
      }
    }
    swap(dp1, dp2);
    dp2.clear();
  }
  println(1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
