/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 1'000;
constexpr int N = 200;
constexpr int A = 1'000'000'000;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, T, "t");
  inf.readEoln();
  for (int i = 1; i <= t; i++) {
    setTestCase(i);
    auto n = inf.readInt(1, N, "n");
    inf.readSpace();
    inf.readInt(0, n - 1, "k");
    inf.readEoln();
    inf.readInts(n, 1, A, "a");
    inf.readEoln();
  }
  inf.readEof();
}
