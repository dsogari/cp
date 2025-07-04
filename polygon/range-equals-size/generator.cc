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
  auto M = opt(4, 1);
  println(t);
  for (auto n : rnd.partition(t, N, M)) {
    auto mid = rnd.next(n + 1, A - n);
    vector<int> a(n);
    for (int j = 0; j < n; j++) {
      a[j] = rnd.next(mid - n, mid + n);
    }
    println(n);
    println(a);
  }
}
