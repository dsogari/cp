#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

void run()
{
  int x;
  cin >> x;
  const auto f = [](int x)
  {
    return x - 1;
  };
  cout << f(x) << endl;
}

int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  int c;
  cin >> c;
  while (c--)
    run();
}