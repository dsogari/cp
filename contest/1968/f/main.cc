/**
 * https://codeforces.com/contest/1968/submission/267259391
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, q;
  cin >> n >> q;
  vector<int> b(n + 1);
  map<int, vector<int>> p;
  p[0].push_back(0);
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    b[i] ^= b[i - 1];
    p[b[i]].push_back(i);
  }
  auto f = [&](int l, int r) {
    auto bl = b[l - 1], br = b[r];
    if (bl == br) {
      return true;
    }
    auto s = ranges::lower_bound(p[br], l);
    auto t = ranges::lower_bound(p[bl], r);
    return *s < *prev(t);
  };
  for (int i = 0, l, r; i < q; ++i) {
    cin >> l >> r;
    auto ans = f(l, r) ? "YES" : "NO";
    cout << ans << endl;
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