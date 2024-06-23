#include "utils.h"

IO(__FILE__);

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