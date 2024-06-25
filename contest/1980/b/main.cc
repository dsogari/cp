/**
 * https://codeforces.com/contest/1980/submission/267273941
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, f, k;
  cin >> n >> f >> k;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  if (k == n) {
    cout << "YES" << endl;
    return;
  }
  auto x = a[f];
  ranges::sort(a, greater<int>());
  auto ans = a[k - 1] > x ? "NO" : (a[k] < x ? "YES" : "MAYBE");
  cout << ans << endl;
}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input.txt").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}