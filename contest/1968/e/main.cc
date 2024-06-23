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

struct Point
{
  int r, c;
};

void solve(int t)
{
  int n;
  in >> n;
  const auto f = [n]()
  {
    vector<Point> h(n);
    for (int i = 0; i < n; ++i)
      h[i] = {i + 1, i + 1};
    h[1].c = 1;
    return h;
  };
  for (const auto p : f())
    out << p.r << " " << p.c << endl;
  out << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}