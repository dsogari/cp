#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n;
  in >> n;
  int best = 0;
  for (int x = 2, mx = 0; x <= n; ++x)
  {
    const auto k = n / x, sum = x * k * (k + 1) / 2;
    if (sum > mx)
    {
      mx = sum;
      best = x;
    }
  }
  cout << best << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}