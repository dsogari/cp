/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 1'000;
constexpr int A = 1'000'000'000;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, T, "t");
  inf.readEoln();
  for (int i = 1; i <= t; i++) {
    setTestCase(i);
    auto l = inf.readInt(-A, A, "l");
    inf.readSpace();
    inf.readInt(l, A, "r");
    inf.readEoln();
  }
  inf.readEof();
}
