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

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  map<array<int, 3>, i64> memo;
  auto dfs = [&](auto &dfs, int i, int l, int r, int c) -> i64 {
    if (i >= n) {
      return max({+n, n - l + k, r + 1 + k}) <= (2 * k + 1) * c ? 0 : INT_MAX;
    }
    auto &ans = memo.insert({{i, l, c}, -1}).first->second;
    if (ans < 0) {
      auto ans1 = dfs(dfs, i + 1 + k, c > 0 ? l : i, i, c + 1) + a[i];
      auto ans2 = dfs(dfs, i + 1, l, r, c);
      ans = min(ans1, ans2);
    }
    return ans;
  };
  auto ans = dfs(dfs, 0, 0, 0, 0); // O(n^3*log n)
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
