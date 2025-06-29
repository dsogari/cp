/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto t = opt(1, 1'000);
  auto N = opt(2, 1'000);
  auto M = opt(3, 1);
  println(t);
  for (auto n : rnd.partition(t, N, M)) {
    auto s = rnd.next("[a-z]{%d}", n);
    for (int i = 1; i < n; i++) {
      while (s[i] == s[i - 1]) {
        s[i] = rnd.next('a', 'z');
      }
    }
    println(s);
  }
}
