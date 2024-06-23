#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int x;
  in >> x;
  const auto f = [x]()
  {
    return x - 1;
  };
  out << f() << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}