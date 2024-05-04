#include "utils.h"

void run(istream &in, ostream &out, int t)
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
  INPUT(__FILE__);
  int c;
  input >> c;
  for (int i = 1; i <= c; ++i)
    run(input, cout, i);
}