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
  int n;
  string s;
  in >> n >> s;
  if (n == 2)
  {
    out << stoi(s) << endl;
    return;
  }
  if (n == 3)
  {
    auto res = min(stoi(s.substr(0, 1)) * stoi(s.substr(1, 2)), stoi(s.substr(0, 2)) * stoi(s.substr(2, 1)));
    out << res << endl;
    return;
  }
  if (s.find('0') != string::npos)
  {
    out << 0 << endl;
    return;
  }
  int imin = 0;
  for (int i = 1; i < n - 1; i++)
  {
    if (s[i] <= s[imin] && s[i + 1] != '1' && (s[imin + 1] == '1' || s[i + 1] < s[imin + 1]))
    {
      imin = i;
    }
  }
  int res = 0;
  for (int i = 0; i < n; i++)
  {
    if (i == imin)
    {
      res += stoi(s.substr(i, 2));
      i++;
    }
    else if (s[i] != '1')
    {
      res += s[i] - '0';
    }
  }
  out << res << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}