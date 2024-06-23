#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, m;
  cin >> n >> m;
  int h = 0, k = 0;
  bool end = false;
  for (int i = 0; i < n; ++i) {
    string row;
    cin >> row;
    if (!k) {
      const auto pos = row.find('#');
      if (pos != string::npos) {
        k = pos + 1;
        h = i + 1;
      }
    } else if (!end) {
      const auto pos = row.find('#');
      if (pos == string::npos) {
        h = ((i + 1) + h) / 2;
        end = true;
      }
    }
  }
  if (!end) {
    h = (n + h) / 2;
  }
  cout << h << " " << k << endl;
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