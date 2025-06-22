/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

using namespace std;

constexpr int T = 10'000;
constexpr int N = 1'000;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, T, "t");
  inf.readEoln();
  for (int i = 1; i <= t; i++) {
    setTestCase(i);
    auto n = inf.readInt(1, N, "n");
    inf.readSpace();
    auto m = inf.readInt(1, N, "m");
    inf.readEoln();
    auto A = max(n, m);
    for (int k = 0; k < n; k++) {
      inf.readInts(m, 0, A, "a");
      inf.readEoln();
    }
  }
  inf.readEof();
}
