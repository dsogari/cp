#include "utils.h"

IO(__FILE__);

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