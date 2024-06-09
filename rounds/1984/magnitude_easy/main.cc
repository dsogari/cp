#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n;
  in >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i)
    in >> v[i];
  i64 a = 0, b = 0;
  for (int i = 0; i < n; ++i)
  {
    const auto c = a + v[i], d = b + v[i];
    a = min(c, d);
    b = max(abs(c), abs(d));
  }
  cout << max(abs(a), abs(b)) << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}