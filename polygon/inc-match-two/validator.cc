/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxn = 5e3;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto s = inf.readWord(format("[a-z]{1,%d}", maxn), "s");
    for (int i = 1; i < s.size(); i++) {
      ensuref(s[i] != s[i - 1], "equal characters at position %d", i + 1);
    }
    inf.readEoln();
  }
  inf.readEof();
}
