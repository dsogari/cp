#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

struct Point {
  int r, c;
};

void solve(int t) {
  int n;
  cin >> n;
  const auto f = [n]() {
    vector<Point> h(n);
    for (int i = 0; i < n; ++i) {
      h[i] = {i + 1, i + 1};
    }
    h[1].c = 1;
    return h;
  };
  for (const auto p : f()) {
    cout << p.r << " " << p.c << endl;
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