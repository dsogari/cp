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
  int matrix[n][m];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      in >> matrix[i][j];
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      auto a = i > 0 ? matrix[i - 1][j] : 0;
      auto b = j > 0 ? matrix[i][j - 1] : 0;
      auto c = i < n - 1 ? matrix[i + 1][j] : 0;
      auto d = j < m - 1 ? matrix[i][j + 1] : 0;
      auto e = max(a, max(b, max(c, d)));
      if (matrix[i][j] > e)
      {
        matrix[i][j] = e;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      out << matrix[i][j] << ' ';
    }
    out << endl;
  }
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}