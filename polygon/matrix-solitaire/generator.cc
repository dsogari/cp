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
  auto type = opt(4, 1);
  println(t);
  for (auto l : rnd.partition(t, N, M)) {
    l /= 2;
    int n = ceil(sqrt(l) * rnd.next(0.5, 2.0));
    int m = l / min(n, l) * 2;
    println(n, m);
    vector<int> a(m);
    if (type == 1) {
      auto p = rnd.perm(n * m);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          a[j] = p[i * m + j] / 2 + 1;
        }
        println(a);
      }
    } else {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
          a[j] = (m / 2) * (i + 1) - j;
        }
        for (int j = m / 2; j < m; j++) {
          a[j] = (m / 2) * i + j + 1 - m / 2;
        }
        if (i > 0) {
          a[m / 2]--;
        }
        if (i < n - 1) {
          a[m - 1]++;
        }
        println(a);
      }
    }
  }
}
