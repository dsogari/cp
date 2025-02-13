/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 250, maxn = 18, maxa = 1e9;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int N = opt<int>(2, maxn);
  int A = opt<int>(3, maxa);
  int minn = opt<int>(4, 1);
  auto lengths = rnd.partition(t, 1 << N, 1 << minn);
  println(t);
  for (int i = 0; i < t; i++) {
    auto n = std::bit_width<unsigned>(lengths[i]) - 1;
    println(n);
    for (int j = 0; j < n; j++) {
      auto w = rnd.next(1, A);
      auto h = rnd.next(1, A);
      println(w, h);
    }
  }
}
