#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n, m;
  in >> n >> m;
  string a;
  in >> a;
  vector<int> hist(7);
  for (char c : a)
    hist[c - 'A']++;
  int res = 0;
  for (int r : hist)
    if (r < m)
      res += m - r;
  cout << res << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}