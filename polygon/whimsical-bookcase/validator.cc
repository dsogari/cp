/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 10'000;
constexpr int N = 200'000;
constexpr int A = 1'000'000'000;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, T, "t");
  inf.readEoln();
  for (int i = 1; i <= t; i++) {
    setTestCase(i);
    auto n = inf.readInt(1, N, "n");
    inf.readEoln();
    for (int j = 0; j < n; j++) {
      inf.readInt(1, A, "w");
      inf.readSpace();
      inf.readInt(1, A, "h");
      inf.readEoln();
    }
  }
  inf.readEof();
}
