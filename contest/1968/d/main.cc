/**
 * https://codeforces.com/contest/1968/submission/267257471
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

void solve(int t) {
  int n, k, pb, ps;
  cin >> n >> k >> pb >> ps;
  vector<int> p(n + 1), a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  auto f = [&](int k, int n, int i) {
    i64 mx = 0;
    for (i64 sum = 0; k && n; --k, --n, sum += a[i], i = p[i]) {
      mx = max(mx, sum + i64(k) * a[i]);
    }
    return mx;
  };
  auto fb = f(k, n, pb);
  auto fs = f(k, n, ps);
  auto wn = fb > fs ? "Bodya" : (fb < fs ? "Sasha" : "Draw");
  cout << wn << endl;
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