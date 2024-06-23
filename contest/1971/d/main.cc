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
  string s;
  in >> s;
  int r = 0, c0 = false, prev = ' ';
  for (const auto c : s)
  {
    if (c != prev)
    {
      if (prev == ' ' || c == '0' || c0)
        ++r;
      else
        c0 = true;
      prev = c;
    }
  }
  out << r << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}