/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto t = opt(1, 10'000);
  auto N = opt(2, 200'000);
  auto A = opt(3, 1'000'000'000);
  auto K = opt(4, N);
  auto M = opt(5, 1);
  println(t);
  for (auto n : rnd.partition(t, N, M)) {
    auto k = rnd.next(1, min(n, K));
    println(n, k);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = rnd.next(1, A);
    }
    println(a);
  }
}
