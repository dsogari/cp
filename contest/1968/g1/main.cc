/**
 * https://codeforces.com/contest/1968/submission/267599226
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

vector<int> zfunc(const string &s) {
  const int n = s.size();
  vector<int> z(n);
  for (int i = 1, j = 1; i < n; i++) {
    if (i < j + z[j]) {
      z[i] = min(j + z[j] - i, z[i - j]);
    }
    for (; i + z[i] < n && s[i + z[i]] == s[z[i]]; z[i]++, j = i)
      ;
  }
  return z;
}

void solve(int t) {
  int n, k;
  string s;
  cin >> n >> k >> k >> s;
  auto z = zfunc(s);
  auto f = [&](int x) {
    int c = 1;
    for (int i = x; i <= n - x; i++) {
      if (z[i] >= x) {
        i += x - 1;
        c++;
      }
    }
    return c;
  };
  int ans = 1;
  for (int end = n; ans <= end;) {
    auto mid = (ans + end) / 2;
    if (f(mid) >= k) {
      ans = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  cout << ans - 1 << endl;
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