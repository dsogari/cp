#include "utils.h"

void run(istream &in, ostream &out, int t)
{
  int x, y;
  string a, b;
  in >> x >> y >> a >> b;
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
  out << f() << endl;
}

int main()
{
  INPUT(__FILE__);
  int c;
  input >> c;
  for (int i = 1; i <= c; ++i)
    run(input, cout, i);
}