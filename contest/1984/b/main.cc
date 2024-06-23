#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  i64 x;
  cin >> x;
  if (x % 10 == 9) {
    cout << "NO" << endl;
    return;
  }
  auto dn = 0;
  while (x) {
    dn = x;
    x /= 10;
    if (x && x % 10 == 0) {
      cout << "NO" << endl;
      return;
    }
  }
  if (dn != 1) {
    cout << "NO" << endl;
    return;
  }
  cout << "YES" << endl;
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