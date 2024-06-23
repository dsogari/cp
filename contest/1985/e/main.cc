#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int x, y, z;
  cin >> x >> y >> z;
  i64 k;
  cin >> k;
  vector<int> factors;
  while (k & 1 == 0) {
    factors.push_back(2);
    k >>= 1;
  }
  for (int i = 3; k > 1;) {
    const auto r = k / i;
    if (r * i == k) {
      factors.push_back(i);
      k = r;
    } else {
      i += 2;
    }
  }
  if (factors.size() < 3) {
    cout << 0 << endl;
  }
  int res = 0;
  for (int i = 0, a = 1, c = 1; i < factors.size() - 2; ++i, c = 1) {
    a *= factors[i];
    c *= x - a;
    for (int j = i + 1, b = 1; j < factors.size() - 2; ++j) {
      b *= factors[i];
      c *= x - b;
      for (int k = j + 1, c = 1; k < factors.size() - 2; ++k) {
        c *= factors[i];
        c *= x - c;
      }
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