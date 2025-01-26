/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e4, maxn = 2e5, maxa = 1e9, maxh = 1e9;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int N = opt<int>(2, maxn);
  int R = opt<int>(3, maxa);
  int H = opt<int>(4, maxh);
  int minn = opt<int>(5, 2);
  auto lengths = rnd.partition(t, N, minn);
  println(t);
  for (int i = 0; i < t; i++) {
    auto n = lengths[i];
    println(n);
    std::set<std::array<int, 2>> used;
    for (int j = 0; j < n; j++) {
      auto x = rnd.next(-R, R);
      auto y = rnd.next(-R, R);
      auto h = rnd.next(1, H);
      if (!used.insert({x, y}).second) {
        j--;
        continue;
      }
      println(x, y, h);
    }
  }
}
