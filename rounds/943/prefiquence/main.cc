#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

void run()
{
  int x, y;
  string a, b;
  cin >> x >> y >> a >> b;
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
  cout << f() << endl;
}

int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  int c;
  cin >> c;
  while (c--)
    run();
}