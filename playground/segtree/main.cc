/**
 * (c) 2024 Diego Sogari
 */
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
    auto [l, r] = minmax({rand() % n, rand() % n});
    q[i] = {rand() % 4, l, r, rand() % mx};
  }
  vector<int> pref(n);
  PushSegTree<Seg, Lazy<int>> st(n);
  for (int i = 0; i < n; i++) {
    st[i] = {pref[i] = rand() % mx};
  }
  st.update();
  assert(*ranges::max_element(pref) == st.full().x);
  chrono::duration<double, milli> ms;
  auto upd = [&](int l, int r, int x, int op) {
    for (int i = l; i <= r; i++) {
      pref[i] = op == 0 ? x : op == 1 ? pref[i] + x : x + i;
    }
    auto t0 = now();
    if (op == 2) {
      st.push(l, r);
      for (int i = l; i <= r; i++) {
        st[i] = {x + i};
        st.lazy[i + n] = {}; // discard lazy values
      }
      st.update(l, r);
    } else {
      st.update(l, r, {x, !op});
    }
    ms += now() - t0;
  };
  auto chk = [&](int l, int r) {
    auto t0 = now();
    auto ans = st.query(l, r);
    ms += now() - t0;
    auto ans2 = reduce(pref.begin() + l, pref.begin() + r + 1, 0, imax<int>);
    assert(ans2 == ans.x);
  };
  for (auto [op, l, r, x] : q) {
    op <= 2 ? upd(l, r, x, op) : chk(l, r);
  }
  st.push();
  assert(*ranges::max_element(pref) == st.full().x);
  for (int i = 0; i < n; i++) {
    assert(pref[i] == st.get(i).x);
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
