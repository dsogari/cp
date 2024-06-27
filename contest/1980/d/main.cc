/**
 * https://codeforces.com/contest/1980/submission/267648211
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  a[0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int j = 0;
  for (int i = 1, prevg = 1; i <= n; i++) {
    auto curg = gcd(a[i], a[i - 1]);
    if (curg < prevg) {
      j = i - 1;
      break;
    }
    prevg = curg;
  }
  if (j == 0) {
    cout << "YES" << endl;
    return;
  }
  assert(j > 1 && j < n);
  for (int k = 0; k < 3; k++) {
    bool ok = true;
    for (int i = 1, prevg = 1; i <= n; i++) {
      int cura = a[i], preva = a[i - 1];
      if (i + 1 == j + k) {
        if (i == n) {
          break;
        }
        cura = a[++i];
      }
      auto curg = gcd(cura, preva);
      if (curg < prevg) {
        ok = false;
        break;
      }
      prevg = curg;
    }
    if (ok) {
      cout << "YES" << endl;
      return;
    }
  }
  cout << "NO" << endl;
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