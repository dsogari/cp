#include "utils.h"

IO(__FILE__);

void solve(int t)
{
  int n, k, pb, ps;
  in >> n >> k >> pb >> ps;
  vector<int> p(n + 1), a(n + 1);
  for (int i = 1; i <= n; ++i)
    in >> p[i];
  for (int i = 1; i <= n; ++i)
    in >> a[i];
  const auto f = [&p, &a](int n, int k, int i)
  {
    i64 r = 0;
    for (i64 s = 0; k && n; --k, --n, s += a[i], i = p[i])
      r = max(r, s + i64(k) * a[i]);
    return r;
  };
  const auto fb = f(n, k, pb);
  const auto fs = f(n, k, ps);
  const auto winner = fb > fs ? "Bodya" : (fb < fs ? "Sasha" : "Draw");
  out << winner << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}