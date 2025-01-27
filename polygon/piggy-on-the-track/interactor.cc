/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxn = 1e4;

int check(int n, int x, int d) {
  println(n);
  std::array<int, 2> end = {1, n}, inc = {-1, 1};
  for (int rem = n + 1; rem--; x == end[d] ? x = end[!d] : x += inc[d]) {
    auto type = ouf.readToken("[!?]");
    if (type == "!") {
      auto y = ouf.readInt(0, 1, "d");
      return y == d;
    } else if (rem > 0) {
      auto y = ouf.readInt(1, n, "p");
      println(y == x);
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  registerInteraction(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  println(t);
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(3, maxn, "n");
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
