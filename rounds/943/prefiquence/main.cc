#include "utils.h"

INPUT(__FILE__)

void run(int c)
{
  int x, y;
  string a, b;
  input >> x >> y >> a >> b;
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
  int c;
  input >> c;
  for (int i = 1; i <= c; ++i)
    run(i);
}