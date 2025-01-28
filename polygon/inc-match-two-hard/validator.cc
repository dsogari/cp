/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e4, maxn = 2e5;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(1, maxn, "n");
    inf.readEoln();
    auto s = inf.readWord(format("[a-z]{%d}", n), "s");
    for (int i = 1; i < n; i++) {
      ensuref(s[i] != s[i - 1], "equal characters at position %d", i);
    }
    inf.readEoln();
  }
  inf.readEof();
}
