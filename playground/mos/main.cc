/**
 * (c) 2024 Diego Sogari
 */
#include "math/order.h"
#include "math/prefix.h"
#include "tree/mos.h"

#include "debug.h"
init();

void solve(int t) {
  srand(time(0));
  Int n, m, mx;
  vector<array<int, 2>> q(m);
  for (int i = 0; i < m; i++) {
    q[i] = {rand() % n, rand() % n};
    if (q[i][0] > q[i][1]) {
      swap(q[i][0], q[i][1]); // [l, r]
    }
  }
  vector<int> ans(m), ans1(m);
  Pref1D<int> pref(n);
  for (int i = 0; i < n; i++) {
    pref[i] = rand() % mx;
  }
  for (int i = 0; i < m; i++) {
    auto [l, r] = q[i];
    ans[i] = pref.query(l, r);
  }
  int acc = 0;
  auto add = [&](int i) { acc += pref[i]; };
  auto rem = [&](int i) { acc -= pref[i]; };
  auto get = [&](int j) { ans1[j] = acc; };
  auto blocksize = sqrt<int>(n);
  Mos mos(m);
  mos.sort(q, bind(evenodd, blocksize, _1, _2));
  auto t0 = now();
  mos.visit(q, add, rem, get, 0);
  auto t1 = now();
  assert(ans == ans1);
  chrono::duration<double, milli> ms1 = t1 - t0;
  mos.sort(q, hilbert);
  t0 = now();
  acc = 0;
  mos.visit(q, add, rem, get, 0);
  t1 = now();
  assert(ans == ans1);
  chrono::duration<double, milli> ms2 = t1 - t0;
  mos.sort(q, [](int l, int r) { return hilbert(l, r - l); });
  t0 = now();
  acc = 0;
  mos.visit(q, add, rem, get, 0);
  t1 = now();
  assert(ans == ans1);
  chrono::duration<double, milli> ms3 = t1 - t0;
  println("OK", ms1.count(), ms2.count(), ms3.count());
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
