#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int x, y;
  string a, b;
  cin >> x >> y >> a >> b;
  const auto f = [&a, &b]() {
    int k = 0;
    for (int j = 0; k < a.size() && j < b.size(); ++j) {
      if (a[k] == b[j]) {
        ++k;
      }
    }
    return k;
  };
  cout << f() << endl;
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