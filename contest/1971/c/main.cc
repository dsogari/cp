#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  const auto j = min(a, b);
  const auto k = max(a, b);
  const auto r1 = c > j && c < k && (d < j || d > k);
  const auto r2 = d > j && d < k && (c < j || c > k);
  cout << (r1 || r2 ? "YES" : "NO") << endl;
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