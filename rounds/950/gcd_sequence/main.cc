#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n;
  in >> n;
  vector<int> a(n), b(n - 1);
  for (int i = 0; i < n; ++i)
    in >> a[i];
  for (int i = 0; i < n - 1; ++i)
    b[i] = gcd(a[i], a[i + 1]);
  bool ok = false;
  for (int i = 0; i < n - 2; ++i)
  {
    if (b[i] > b[i + 1])
    {
      const auto g = gcd(a[i], a[i + 2]);
      if (ok || (i > 0 && i < n - 3 && b[i - 1] > g))
      {
        cout << "NO" << endl;
        return;
      }
      b[i + 1] = g;
      ok = true;
    }
  }
  cout << "YES" << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}