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