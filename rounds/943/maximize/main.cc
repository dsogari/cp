#include "utils.h"

void run(istream &in, ostream &out, int t)
{
  int x;
  in >> x;
  const auto f = [x]()
  {
    return x - 1;
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