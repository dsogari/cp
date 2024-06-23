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