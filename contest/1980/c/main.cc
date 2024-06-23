#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, m;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  cin >> m;
  map<int, int> count;
  int di;
  for (int i = 0; i < m; ++i) {
    cin >> di;
    count[di]++;
  }
  bool ok = false;
  for (int i = 0; i < n; ++i) {
    if (a[i] != b[i]) {
      if (!(count[b[i]]--)) {
        cout << "NO" << endl;
        return;
      }
    }
    if (b[i] == di) {
      ok = true;
    }
  }
  cout << (ok ? "YES" : "NO") << endl;
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