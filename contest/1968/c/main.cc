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
  in >> n;
  vector<int> x(n - 1);
  for (int i = 0; i < n - 1; ++i)
    in >> x[i];
  const auto f = [n, &x]()
  {
    vector<int> a(n);
    a[0] = 501;
    for (int i = 0; i < n - 1; ++i)
      a[i + 1] = a[i] + x[i];
    return a;
  };
  for (const auto ai : f())
    out << ai << " ";
  out << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}