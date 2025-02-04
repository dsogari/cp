/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e4, maxn = 2e5, maxa = 1e9;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int N = opt<int>(2, maxn);
  int A = opt<int>(3, maxa);
  int minn = opt<int>(4, 1);
  auto lengths = rnd.partition(t, N, minn);
  println(t);
  for (int i = 0; i < t; i++) {
    auto n = lengths[i];
    println(n);
    for (int j = 0; j < n; j++) {
      auto w = rnd.next(1, A);
      auto h = rnd.next(1, A);
      println(w, h);
    }
  }
}
