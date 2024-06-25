/**
 * https://codeforces.com/contest/1980/submission/267275233
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, m;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  cin >> m;
  map<int, int> count;
  int d;
  for (int i = 0; i < m; ++i) {
    cin >> d;
    count[d]++;
  }
  bool ans = false;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      auto c = count[b[i]]--;
      if (!c) {
        cout << "NO" << endl;
        return;
      }
    }
    if (b[i] == d) {
      ans = true;
    }
  }
  cout << (ans ? "YES" : "NO") << endl;
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