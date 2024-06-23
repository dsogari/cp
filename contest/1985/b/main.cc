#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n;
  cin >> n;
  int best = 0;
  for (int x = 2, mx = 0; x <= n; ++x) {
    const auto k = n / x, sum = x * k * (k + 1) / 2;
    if (sum > mx) {
      mx = sum;
      best = x;
    }
  }
  cout << best << endl;
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