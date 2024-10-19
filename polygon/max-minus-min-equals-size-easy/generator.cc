/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"
#include <numeric>

constexpr int maxt = 1e4, maxn = 2e5;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  int t = opt<int>(1, maxt);
  int N = opt<int>(2, maxn);
  int minn = opt<int>(3, 1);
  auto lengths = rnd.partition(t, N, minn);
  println(t);
  for (int i = 0; i < t; i++) {
    auto n = lengths[i];
    std::vector<int> a(2 * n);
    std::iota(a.begin(), a.end(), 1);
    shuffle(a.begin(), a.end());
    a.resize(n);
    println(n);
    println(a);
  }
}
