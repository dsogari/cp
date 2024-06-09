#include "utils.h"

IO(__FILE__);

vector<int> p2(3e5 + 1);

const auto mod = 998244353;

void solve(int t)
{
  int n;
  in >> n;
  i64 sum = 0, min = 0;
  int res = p2[n];
  for (int i = 0, c = 0, a; i < n; ++i)
  {
    in >> a;
    sum += a;
    if (sum >= 0)
      ++c;
    else if (sum < min)
    {
      min = sum;
      res = 0;
    }
    if (sum && sum == min)
      res = (res + p2[c + n - i - 1]) % mod;
  }
  cout << res << endl;
}

int main()
{
  p2[0] = 1;
  for (int i = 1; i < p2.size(); ++i)
    p2[i] = (i64(p2[i - 1]) << 1) % mod;
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}