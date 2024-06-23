#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, m;
  cin >> n >> m;
  string a;
  cin >> a;
  vector<int> hist(7);
  for (char c : a) {
    hist[c - 'A']++;
  }
  int res = 0;
  for (int r : hist) {
    if (r < m) {
      res += m - r;
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