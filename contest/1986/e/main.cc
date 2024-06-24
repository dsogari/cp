#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, k;
  cin >> n >> k;
  map<int, vector<int>> mods;
  for (int i = 0, a; i < n; i++) {
    cin >> a;
    mods[a % k].push_back(a);
  }
  int res = 0, odd = 0;
  for (auto &[_, b] : mods) {
    ranges::sort(b);
    if (b.size() % 2) {
      if (odd++) {
        res = -1;
        break;
      }
      vector<vector<int>> sums = {{0}, {0}};
      for (int i = 0; i < b.size() - 1; i++) {
        sums[i % 2].push_back(sums[i % 2].back() + (b[i + 1] - b[i]) / k);
      }
      int best = INT_MAX;
      for (int i = 0, j = 0; i < b.size(); i += 2, j++) {
        best = min(best, sums[0][j] + sums[1].back() - sums[1][j]);
      }
      res += best;
    } else {
      for (int i = 0; i < b.size(); i += 2) {
        res += (b[i + 1] - b[i]) / k;
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