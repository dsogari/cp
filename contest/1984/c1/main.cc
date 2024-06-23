#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n;
  in >> n;
  i64 sum = 0, res = 0;
  for (int i = 0, a; i < n; ++i)
  {
    in >> a;
    sum += a;
    res = max(abs(sum), abs(res + a));
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