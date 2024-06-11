#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n;
  in >> n;
  set<i64> sums = {0};
  int res = 0;
  i64 sum = 0;
  for (int i = 0, a; i < n; ++i)
  {
    in >> a;
    sum += a;
    sums.insert(2 * a);
    if (sums.count(sum))
      ++res;
  }
  cout << res << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}