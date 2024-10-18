/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxn = 1e4;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(3, maxn, "n");
    inf.readSpace();
    inf.readInt(1, n, "x");
    inf.readSpace();
    inf.readInt(0, 1, "d");
    inf.readEoln();
  }
  inf.readEof();
}
