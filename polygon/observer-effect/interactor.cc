/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 1'000;
constexpr int N = 10'000;

int check(int n, int x, int d) {
  println(n);
  for (int rem = n + 1, end = d ? n : 1, inc = d ? 1 : -1; rem--;
       x == end ? x = n - end + 1 : x += inc) {
    auto type = ouf.readToken("[!?]");
    if (type == "!") {
      auto y = ouf.readInt(0, 1, "d");
      return y == d;
    } else if (rem > 0) {
      auto y = ouf.readInt(1, n, "p");
      println(y == x);
    }
  }
  println(-1);
  return -1;
}

int main(int argc, char *argv[]) {
  registerInteraction(argc, argv);
  auto t = inf.readInt(1, T, "t");
  println(t);
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(3, N, "n");
    auto x = inf.readInt(1, n, "x");
    auto d = inf.readInt(0, 1, "d");
    auto v = check(n, x, d);
    if (v < 0) {
      quitf(_wa, "couldn't guess the answer in %d queries", n);
    } else if (!v) {
      quit(_wa, "");
    }
  }
  quitf(_ok, "%d test cases processed", t);
}
