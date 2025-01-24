/**
 * (c) 2024 Diego Sogari
 */
#include "io.h"
#include "math/order.h"
#include "math/prefix.h"
#include "tree/segment.h"

#include "debug.h"
init();

void solve(int t) {
  srand(time(0));
  Int n, m, mx;
  vector<array<int, 4>> q(m);
  for (int i = 0; i < m; i++) {
    q[i] = {rand() % 3, rand() % n, rand() % n, rand() % mx};
    if (q[i][1] > q[i][2]) {
      swap(q[i][1], q[i][2]); // [l, r]
    }
  }
  Pref1D<int> pref(n, Max<int>{});
  AssignSegTree<int, int> segtree(n, Max<int>{});
  for (int i = 0; i < n; i++) {
    pref[i] = segtree[i] = rand() % mx;
  }
  segtree.update(n - 1, false);
  assert(pref.full() == segtree.full());
  chrono::duration<double, milli> ms;
  auto upd = [&](int l, int r, int x, bool set) {
    for (int i = l; i <= r; i++) {
      pref[i] = set ? x : pref[i] + x;
    }
    auto t0 = now();
    segtree.update(l, r, x, set);
    ms += now() - t0;
  };
  auto chk = [&](int l, int r) {
    auto t0 = now();
    auto ans = segtree.query(l, r);
    ms += now() - t0;
    assert(pref.query(l, r) == ans);
  };
  for (auto [op, l, r, x] : q) {
    op <= 1 ? upd(l, r, x, op) : chk(l, r);
  }
  segtree.pushall(n - 1);
  assert(pref.full() == segtree.full());
  for (int i = 0; i < n; i++) {
    assert(pref[i] == segtree.get(i));
  }
  println("OK", ms.count(), "ms");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
