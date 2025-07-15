/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 10'000;
constexpr int N = 51;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, T, "t");
  inf.readEoln();
  for (int i = 1; i <= t; i++) {
    setTestCase(i);
    auto s = inf.readWord(format("[a-z]{1,%d}", N), "s");
    for (int i = 1; i < s.size(); i++) {
      ensuref(s[i] != s[i - 1], "equal characters at position %d", i + 1);
    }
    inf.readEoln();
  }
  inf.readEof();
}
