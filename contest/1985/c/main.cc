#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n;
  cin >> n;
  set<i64> sums = {0};
  int res = 0;
  i64 sum = 0;
  for (int i = 0, a; i < n; ++i) {
    cin >> a;
    sum += a;
    sums.insert(2 * a);
    if (sums.count(sum)) {
      ++res;
    }
  }
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