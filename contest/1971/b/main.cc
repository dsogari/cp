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