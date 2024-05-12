#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int x, y;
  in >> x >> y;
  out << min(x, y) << ' ' << max(x, y) << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}