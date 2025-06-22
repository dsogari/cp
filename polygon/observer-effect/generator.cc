/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt(1, 1'000);
  int N = opt(2, 10'000);
  int M = opt(3, 3);
  println(t);
  for (auto n : rnd.partition(t, N, M)) {
    auto x = rnd.next(1, n);
    auto d = rnd.next(0, 1);
    println(n, x, d);
  }
}
