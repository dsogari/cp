/**
 * https://codeforces.com/contest/1980/submission/267270098
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, m, l = 'G' - 'A' + 1;
  string a;
  cin >> n >> m >> a;
  vector<int> hist(l);
  for (auto &&c : a) {
    hist[c - 'A']++;
  }
  int ans = 0;
  for (auto &c : hist) {
    if (c < m) {
      ans += m - c;
    }
  }
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