#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, k, q;
  cin >> n >> k >> q;
  vector<int> a(k + 1), b(k + 1);
  for (int i = 1; i <= k; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= k; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < q; ++i) {
    int q;
    cin >> q;
    const auto j = prev(ranges::upper_bound(a, q)) - a.begin();
    if (j < a.size() - 1) {
      const auto r =
          b[j] + (q - a[j]) * ((b[j + 1] - b[j]) / double(a[j + 1] - a[j]));
      cout << int(r) << ' ';
    } else {
      cout << b.back() << ' ';
    }
  }
  cout << endl;
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