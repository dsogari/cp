#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

void run()
{
  int n;
  cin >> n;
  vector<int> x(n - 1);
  for (int i = 0; i < n - 1; ++i)
    cin >> x[i];
  const auto f = [n, &x]()
  {
    vector<int> a(n);
    a[0] = 501;
    for (int i = 0; i < n - 1; ++i)
      a[i + 1] = a[i] + x[i];
    return a;
  };
  for (const auto ai : f())
    cout << ai << " ";
  cout << endl;
}

int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  int c;
  cin >> c;
  while (c--)
    run();
}