#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n, f, k;
  in >> n >> f >> k;
  vector<int> v(n);
  for (int i = 0; i < n; ++i)
    in >> v[i];
  const auto val = v[f - 1];
  const auto cmp = greater<int>();
  ranges::sort(v, cmp);
  const auto l = ranges::lower_bound(v, val, cmp) - v.begin();
  const auto r = ranges::lower_bound(v, val - 1, cmp) - v.begin();
  const auto res = k >= r ? "YES" : (k > l ? "MAYBE" : "NO");
  cout << res << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}