/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxn = 5e3;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int N = opt<int>(2, maxn);
  int minn = opt<int>(3, 1);
  auto lengths = rnd.partition(t, N, minn);
  println(t);
  for (int i = 0; i < t; i++) {
    int n = lengths[i];
    auto s = rnd.next("[a-z]{%d}", n);
    for (int i = 1; i < n; i++) {
      while (s[i] == s[i - 1]) {
        s[i] = rnd.next('a', 'z');
      }
    }
    println(s);
  }
}
