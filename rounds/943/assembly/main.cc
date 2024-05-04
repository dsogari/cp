#include "utils.h"

INPUT(__FILE__)

void run(int c)
{
  int n;
  input >> n;
  vector<int> x(n - 1);
  for (int i = 0; i < n - 1; ++i)
    input >> x[i];
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
  int c;
  input >> c;
  for (int i = 1; i <= c; ++i)
    run(i);
}