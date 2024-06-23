#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, m;
  cin >> n >> m;
  int matrix[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> matrix[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      auto a = i > 0 ? matrix[i - 1][j] : 0;
      auto b = j > 0 ? matrix[i][j - 1] : 0;
      auto c = i < n - 1 ? matrix[i + 1][j] : 0;
      auto d = j < m - 1 ? matrix[i][j + 1] : 0;
      auto e = max(a, max(b, max(c, d)));
      if (matrix[i][j] > e) {
        matrix[i][j] = e;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << matrix[i][j] << ' ';
    }
    cout << endl;
  }
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