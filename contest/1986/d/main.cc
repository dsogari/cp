#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n;
  string s;
  cin >> n >> s;
  int res = INT_MAX;
  for (int i = 0; i < n - 1; i++) {
    int res1 = (s[i] - '0') * 10 + s[i + 1] - '0';
    for (int j = 0; j < n; j++) {
      if (j == i) {
        j++;
        continue;
      }
      if (s[j] == '0') {
        cout << 0 << endl;
        return;
      }
      if (s[j] != '1') {
        if (res1 == 1) {
          res1 = 0;
        }
        res1 += s[j] - '0';
      }
    }
    res = min(res, res1);
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