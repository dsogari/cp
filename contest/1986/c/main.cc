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
  string s, c;
  in >> n >> m >> s;
  vector<int> ind(m);
  for (int i = 0; i < m; i++)
  {
    in >> ind[i];
  }
  in >> c;
  ranges::sort(ind);
  ranges::sort(c);
  for (int i = 0, j = 0, prev = -1; i < m; i++)
  {
    if (ind[i] == prev)
      continue;
    prev = ind[i];
    s[prev - 1] = c[j++];
  }
  out << s << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}