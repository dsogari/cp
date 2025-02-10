/**
 * (c) 2024 Diego Sogari
 */
#include "io.h"
#include "math/order.h"
#include "math/prefix.h"
#include "tree/segment.h"

#include "debug.h"
init();

struct Seg {
  int x;
  Seg(int a = 0) : x(a) {}
  Seg operator+(const Seg &other) const { return max(x, other.x); }
  Seg operator+(const Lazy<Seg, int> &rhs) const {
    return rhs.set ? rhs.val : x + rhs.val;
  }
};

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
  AssignSegTree<Seg, int> st(n);
  for (int i = 0; i < n; i++) {
    st[i] = pref[i] = rand() % mx;
  }
  st.update(n - 1, false);
  assert(pref.full() == st.full().x);
  chrono::duration<double, milli> ms;
  auto upd = [&](int l, int r, int x, bool set) {
    for (int i = l; i <= r; i++) {
      pref[i] = set ? x : pref[i] + x;
    }
    auto t0 = now();
    st.update(l, r, x, set);
    ms += now() - t0;
  };
  auto chk = [&](int l, int r) {
    auto t0 = now();
    auto ans = st.query(l, r);
    ms += now() - t0;
    assert(pref.query(l, r) == ans.x);
  };
  for (auto [op, l, r, x] : q) {
    op <= 1 ? upd(l, r, x, op) : chk(l, r);
  }
  st.pushall(n - 1);
  assert(pref.full() == st.full().x);
  for (int i = 0; i < n; i++) {
    assert(pref[i] == st.query(i, i).x);
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
