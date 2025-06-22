/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 1'000;
constexpr int N = 10'000;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, T, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(3, N, "n");
    inf.readSpace();
    inf.readInt(1, n, "x");
    inf.readSpace();
    inf.readInt(0, 1, "d");
    inf.readEoln();
  }
  inf.readEof();
}
