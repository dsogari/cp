#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, q;
  cin >> n >> q;
  vector<int> b(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    b[i] ^= b[i - 1];
  }
  map<int, vector<int>> p;
  for (int i = 0; i <= n; ++i) {
    p[b[i]].push_back(i);
  }
  const auto f = [&b, &p](int l, int r) {
    const auto bl = b[l - 1];
    const auto br = b[r];
    if (bl == br) {
      return true;
    }
    const auto &pl = p[bl];
    const auto &pr = p[br];
    const auto s = ranges::lower_bound(pr, l);
    const auto t = ranges::lower_bound(pl, r);
    return s < pr.end() && t > pl.begin() && *s < *prev(t);
  };
  for (int l, r; q; --q) {
    cin >> l >> r;
    cout << (f(l, r) ? "YES" : "NO") << endl;
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