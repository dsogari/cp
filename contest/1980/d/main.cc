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

constexpr int inc_mod(int a, int m)
{
  return (a + 1) % m;
}

constexpr int dec_mod(int a, int m)
{
  return (a ? a : m) - 1;
}

void solve(int t)
{
  int n;
  vector<int> a(4), b(4);
  in >> n >> a[0] >> a[1];
  b[1] = gcd(a[0], a[1]);
  for (int i = 2, j = 2, r = 0; i < n; ++i)
  {
    const auto k = dec_mod(j, 4), l = dec_mod(k, 4);
    in >> a[j];
    b[j] = gcd(a[k], a[j]);
    if (b[k] > b[j])
    {
      if (r)
      {
        cout << "NO" << endl;
        return;
      }
      const auto mid = gcd(a[l], a[j]);
      if (b[j] > mid && mid >= b[l])
      {
        a[k] = a[j]; // remove middle
        b[k] = mid;
      }
      else
      {
        const auto m = dec_mod(l, 4);
        const auto b0 = gcd(a[m], a[k]);

        if (b[j] >= b[l])
        {
        }
        a[l] = a[k]; // remove first
        a[k] = a[j];
        b[l] = b[j];
        b[k] = b[j];
      }
      ++r;
    }
    else
    {
      j = inc_mod(j, 4);
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