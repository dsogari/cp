#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, k, pb, ps;
  cin >> n >> k >> pb >> ps;
  vector<int> p(n + 1), a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  const auto f = [&p, &a](int n, int k, int i) {
    i64 r = 0;
    for (i64 s = 0; k && n; --k, --n, s += a[i], i = p[i]) {
      r = max(r, s + i64(k) * a[i]);
    }
    return r;
  };
  const auto fb = f(n, k, pb);
  const auto fs = f(n, k, ps);
  const auto winner = fb > fs ? "Bodya" : (fb < fs ? "Sasha" : "Draw");
  cout << winner << endl;
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