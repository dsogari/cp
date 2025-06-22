/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  auto t = opt(1, 10'000);
  auto N = opt(2, 200'000);
  auto M = opt(3, 1);
  auto type = opt(4, 1);
  println(t);
  for (auto l : rnd.partition(t, N, M)) {
    auto n = (int)ceil(sqrt(l) * rnd.next(0.5, 2.0));
    auto m = l / min(n, l);
    auto A = max(n, m);
    println(n, m);
    vector<int> a(m);
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < m; j++) {
        a[j] = type == 1 ? rnd.wnext(0, A, -1) : k < n - 1 && j < m - 1 ? A : 1;
      }
      println(a);
    }
  }
}
