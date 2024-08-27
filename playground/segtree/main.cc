/**
 * (c) 2024 Diego Sogari
 */
#include "io.h"
#include "math/pref.h"
#include "tree/segment.h"

#include "debug.h"
init();

struct Lazy {
  bool set; // add by default
  int val;
  operator int() const { return val; }
  int merge(int original) const { return set ? val : val + original; }
  Lazy join(const Lazy &rhs) const { return {rhs.set, rhs.merge(val)}; }
};

auto tmerge = bind(&Lazy::merge, _2, _1);

void solve(int t) {
  srand(time(0));
  Int n, m, mx;
  vector<array<int, 4>> q(m);
  for (int i = 0; i < m; i++) {
    q[i] = {rand() % 3, rand() % n, rand() % n, rand() % mx};
    if (q[i][1] > q[i][2]) {
      swap(q[i][1], q[i][2]);
    }
  }
  Pref<int> pref(n, tmax);
  PushSegTree<int, Lazy> segtree(n, tmax, tmerge, &Lazy::join);
  for (int i = 0; i < n; i++) {
    pref[i] = segtree[i] = rand() % mx;
  }
  segtree.update(n - 1, false);
  assert(pref.full() == segtree.full());
  auto upd = [&](int l, int r, int x, bool set) {
    for (int i = l; i <= r; i++) {
      pref[i] = set ? x : pref[i] + x;
    }
    segtree.update(l, r, {set, x});
  };
  for (auto &[op, l, r, x] : q) {
    if (op <= 1) {
      upd(l, r, x, /*op*/ false);
    } else {
      assert(pref.query(l, r) == segtree.query(l, r));
    }
  }
  segtree.pushall(n - 1);
  if (n > 1) {
    assert(pref.full() == segtree.full());
  }
  for (int i = 0; i < n; i++) {
    assert(pref[i] == segtree.lazy[i + n].merge(segtree[i]));
  }
  println("OK");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
