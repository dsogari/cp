#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
auto in = ifstream(filesystem::path(__FILE__).replace_filename("input.txt"));
auto &out = cout << fixed << setprecision(20);
#else
auto &in = (cin.tie(nullptr)->sync_with_stdio(false), cin);
auto &out = cout << fixed << setprecision(20);
#endif

void solve(int t)
{
  i64 x;
  in >> x;
  if (x % 10 == 9)
  {
    cout << "NO" << endl;
    return;
  }
  auto dn = 0;
  while (x)
  {
    dn = x;
    x /= 10;
    if (x && x % 10 == 0)
    {
      cout << "NO" << endl;
      return;
    }
  }
  if (dn != 1)
  {
    cout << "NO" << endl;
    return;
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