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
  int x, y;
  string a, b;
  in >> x >> y >> a >> b;
  const auto f = [&a, &b]()
  {
    int k = 0;
    for (int j = 0; k < a.size() && j < b.size(); ++j)
    {
      if (a[k] == b[j])
        ++k;
    }
    return k;
  };
  out << f() << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}