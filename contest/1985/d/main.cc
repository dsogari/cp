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
  in >> n >> m;
  int h = 0, k = 0;
  bool end = false;
  for (int i = 0; i < n; ++i)
  {
    string row;
    in >> row;
    if (!k)
    {
      const auto pos = row.find('#');
      if (pos != string::npos)
      {
        k = pos + 1;
        h = i + 1;
      }
    }
    else if (!end)
    {
      const auto pos = row.find('#');
      if (pos == string::npos)
      {
        h = ((i + 1) + h) / 2;
        end = true;
      }
    }
  }
  if (!end)
    h = (n + h) / 2;
  cout << h << " " << k << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}