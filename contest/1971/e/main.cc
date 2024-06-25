/**
 * https://codeforces.com/contest/1971/submission/267267828
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, k, q;
  cin >> n >> k >> q;
  vector<int> a(k + 1), b(k + 1);
  for (int i = 1; i <= k; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; ++i) {
    cin >> b[i];
  }
  auto f = [&](int d) {
    int j = prev(ranges::upper_bound(a, d)) - a.begin();
    if (j < a.size() - 1) {
      int ans = b[j] + i64(d - a[j]) * (b[j + 1] - b[j]) / (a[j + 1] - a[j]);
      return ans;
    }
    return b.back();
  };
  for (int i = 0, d; i < q; ++i) {
    cin >> d;
    cout << f(d) << ' ';
  }
  cout << endl;
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