#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  string s;
  cin >> s;
  for (int i = 1; i < s.size(); ++i) {
    if (s[i] != s[0]) {
      swap(s[i], s[0]);
      cout << "YES" << endl << s << endl;
      return;
    }
  }
  cout << "NO" << endl;
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