/**
 * (c) 2024-2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxa = 1e9;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int L = opt<int>(2, -maxa);
  int R = opt<int>(3, maxa);
  println(t);
  for (int i = 0; i < t; i++) {
    auto l = rnd.next(L, R);
    auto r = rnd.next(l, R);
    println(l, r);
  }
}
