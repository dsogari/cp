#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, f, k;
  cin >> n >> f >> k;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  const auto val = v[f - 1];
  const auto cmp = greater<int>();
  ranges::sort(v, cmp);
  const auto l = ranges::lower_bound(v, val, cmp) - v.begin();
  const auto r = ranges::lower_bound(v, val - 1, cmp) - v.begin();
  const auto res = k >= r ? "YES" : (k > l ? "MAYBE" : "NO");
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