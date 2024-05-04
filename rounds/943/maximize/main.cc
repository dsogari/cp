#include "utils.h"

INPUT(__FILE__)

void run(int c)
{
  int x;
  input >> x;
  const auto f = [x]()
  {
    return x - 1;
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