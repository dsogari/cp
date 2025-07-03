/**
 * https://codeforces.com/contest/2114/submission/327203262
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
  Int x, y, k;
  auto f = [&](int x) { // O(n)
    if (x == 1) {
      return 0;
    }
    vector<int> divs;
    for (int i = 1; i * i <= x; i++) { // O(sqrt n)
      if (x % i == 0) {
        divs.push_back(i);
        divs.push_back(x / i);
      }
    }
    ranges::sort(divs);
    auto m = divs.size();
    vector<int> dp(m, m + 1);
    dp[0] = 0;
    for (int i = 1; i < m; i++) { // O(n)
      for (int j = 0; j < i; j++) {
        auto d = div(divs[i], divs[j]);
        if (d.rem == 0 && d.quot <= k) {
          dp[i] = min(dp[i], dp[j] + 1);
        }
      }
    }
    return dp.back() > m ? -1 : dp.back();
  };
  auto g = gcd(+x, +y);
  auto a = f(x / g);
  auto b = f(y / g);
  if (a < 0 || b < 0) {
    return println(-1);
  }
  auto ans = a + b;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
