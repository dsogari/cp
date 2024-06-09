#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n;
  in >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i)
    in >> v[i];
  if (v[0] == v[n - 1])
  {
    cout << "NO" << endl;
    return;
  }
  cout << "YES" << endl;
  for (int i = 0; i < n; ++i)
    cout << (i == 1 ? "R" : "B");
  cout << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}