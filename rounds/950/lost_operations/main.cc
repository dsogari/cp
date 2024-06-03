#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n, m;
  in >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i)
    in >> a[i];
  for (int i = 0; i < n; ++i)
    in >> b[i];
  in >> m;
  map<int, int> count;
  int di;
  for (int i = 0; i < m; ++i)
  {
    in >> di;
    count[di]++;
  }
  bool ok = false;
  for (int i = 0; i < n; ++i)
  {
    if (a[i] != b[i])
    {
      if (!(count[b[i]]--))
      {
        cout << "NO" << endl;
        return;
      }
    }
    if (b[i] == di)
      ok = true;
  }
  cout << (ok ? "YES" : "NO") << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}