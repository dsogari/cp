#include "utils.h"

IO(__FILE__);

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