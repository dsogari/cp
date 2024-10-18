/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1);
  int N = opt<int>(2);
  println(t);
  for (int i = 0; i < t; i++) {
    auto n = rnd.next(3, N);
    auto x = rnd.next(1, n);
    auto d = rnd.next(0, 1);
    println(n, x, d);
  }
}
