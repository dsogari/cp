/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto t = opt(1, 10'000);
  auto N = opt(2, 200'000);
  auto A = opt(3, 1'000'000'000);
  auto M = opt(4, 1);
  println(t);
  for (auto n : rnd.partition(t, N, M)) {
    println(n);
    for (int i = 0; i < n; i++) {
      auto w = rnd.next(1, A);
      auto h = rnd.next(1, A);
      println(w, h);
    }
  }
}
