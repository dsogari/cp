/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto t = opt(1, 10'000);
  auto N = opt(2, 200'000);
  auto M = opt(3, 2);
  println(t);
  for (auto l : rnd.partition(t, N, M)) {
    l /= 2;
    int n = ceil(sqrt(l) * rnd.next(0.5, 2.0));
    int m = l / min(n, l) * 2;
    println(n, m);
    auto p = rnd.perm(n * m);
    vector<int> a(m);
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < m; j++) {
        a[j] = p[k * m + j] / 2 + 1;
      }
      println(a);
    }
  }
}
