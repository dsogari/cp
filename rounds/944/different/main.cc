#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  string s;
  in >> s;
  for (int i = 1; i < s.size(); ++i)
  {
    if (s[i] != s[0])
    {
      swap(s[i], s[0]);
      out << "YES" << endl
          << s << endl;
      return;
    }
  }
  out << "NO" << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}