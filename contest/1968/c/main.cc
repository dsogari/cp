#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n;
  cin >> n;
  vector<int> x(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    cin >> x[i];
  }
  const auto f = [n, &x]() {
    vector<int> a(n);
    a[0] = 501;
    for (int i = 0; i < n - 1; ++i) {
      a[i + 1] = a[i] + x[i];
    }
    return a;
  };
  for (const auto ai : f()) {
    cout << ai << " ";
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