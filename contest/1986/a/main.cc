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
  int x1, x2, x3;
  in >> x1 >> x2 >> x3;
  auto d1 = abs(x2 - x3);
  auto d2 = abs(x1 - x3);
  auto d3 = abs(x1 - x2);
  auto res = min(min(d1 + d2, d2 + d3), d1 + d3);
  out << res << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}