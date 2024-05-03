#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

void run()
{
  int n, k, pb, ps;
  cin >> n >> k >> pb >> ps;
  vector<int> p(n + 1), a(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> p[i];
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
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
  cout << winner << endl;
}

int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  int c;
  cin >> c;
  while (c--)
    run();
}