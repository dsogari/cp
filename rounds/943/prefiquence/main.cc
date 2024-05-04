#include "utils.h"

IO(__FILE__);

void run(int t)
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
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    run(i);
}