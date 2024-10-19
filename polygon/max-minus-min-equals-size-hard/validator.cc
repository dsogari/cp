/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e4, maxn = 2e5, maxa = 1e6;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(1, maxn, "n");
    inf.readEoln();
    inf.readInts(n, 1, maxa, "a");
    inf.readEoln();
  }
  inf.readEof();
}
