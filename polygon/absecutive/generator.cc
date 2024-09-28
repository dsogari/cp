/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1);
  int L = opt<int>(2);
  int R = opt<int>(3);
  println(t);
  for (int i = 0; i < t; i++) {
    auto l = rnd.next(L, R);
    println(l, rnd.next(l, R));
  }
}
