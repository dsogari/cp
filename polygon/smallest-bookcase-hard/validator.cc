/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 250, maxn = 18, maxa = 1e9;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(1, maxn, "n");
    inf.readEoln();
    for (int j = 0; j < n; j++) {
      inf.readInt(1, maxa, "w");
      inf.readSpace();
      inf.readInt(1, maxa, "h");
      inf.readEoln();
    }
  }
  inf.readEof();
}
