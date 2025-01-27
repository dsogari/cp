/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxn = 5e3, maxa = 1e9, maxh = 1e9;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(2, maxn, "n");
    inf.readEoln();
    std::set<std::array<int, 2>> used;
    for (int j = 0; j < n; j++) {
      auto x = inf.readInt(-maxa, maxa, "x");
      inf.readSpace();
      auto y = inf.readInt(-maxa, maxa, "y");
      inf.readSpace();
      inf.readInt(1, maxh, "h");
      inf.readEoln();
      auto ok = used.insert({x, y}).second;
      ensuref(ok, "duplicate tree at location (%d,%d)", x, y);
    }
  }
  inf.readEof();
}
