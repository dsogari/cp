/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e4, maxn = 2e5, maxa = 1e9;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int N = opt<int>(2, maxn);
  int minn = opt<int>(3, 1);
  auto lengths = rnd.partition(t, N, minn);
  println(t);
  for (int i = 0; i < t; i++) {
    auto n = lengths[i];
    std::vector<int> a(n);
    a[0] = rnd.next(-maxa, maxa);
    auto from = std::max(-maxa, a[0] - n);
    auto to = std::min(maxa, a[0] + n);
    for (int j = 1; j < n; j++) {
      a[j] = rnd.next(from, to);
    }
    println(n);
    println(a);
  }
}
