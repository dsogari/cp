/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int T = 1'000;
constexpr int A = 1'000'000'000;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto t = opt(1, T);
  auto L = opt(2, -A);
  auto R = opt(3, A);
  println(t);
  for (int i = 0; i < t; i++) {
    auto l = rnd.next(L, R);
    auto r = rnd.next(l, R);
    println(l, r);
  }
}
