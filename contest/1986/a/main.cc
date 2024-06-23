#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int x1, x2, x3;
  cin >> x1 >> x2 >> x3;
  auto d1 = abs(x2 - x3);
  auto d2 = abs(x1 - x3);
  auto d3 = abs(x1 - x2);
  auto res = min(min(d1 + d2, d2 + d3), d1 + d3);
  cout << res << endl;
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