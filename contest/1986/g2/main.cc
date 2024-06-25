#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n;
  cin >> n;
  int res = 0;
  for (int i = 1, p; i <= n; i++) {
    cin >> p;
    res += max(0, p - i);
  }
  cout << (res ? res : n * (n - 1)) / 2 << endl;
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