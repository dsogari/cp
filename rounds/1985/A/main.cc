#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  string a, b;
  in >> a >> b;
  swap(a[0], b[0]);
  cout << a << " " << b << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}