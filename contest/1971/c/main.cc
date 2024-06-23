#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
auto in = ifstream(filesystem::path(__FILE__).replace_filename("input.txt"));
auto &out = cout << fixed << setprecision(20);
#else
auto &in = (cin.tie(nullptr)->sync_with_stdio(false), cin);
auto &out = cout << fixed << setprecision(20);
#endif

void solve(int t)
{
  int a, b, c, d;
  in >> a >> b >> c >> d;
  const auto j = min(a, b);
  const auto k = max(a, b);
  const auto r1 = c > j && c < k && (d < j || d > k);
  const auto r2 = d > j && d < k && (c < j || c > k);
  out << (r1 || r2 ? "YES" : "NO") << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}