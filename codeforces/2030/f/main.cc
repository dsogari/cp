/**
 * https://codeforces.com/contest/2030/submission/305448385
 *
 * Fenwick tree; two pointers; greedy
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u32 = uint32_t;
using u64 = uint64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  FenTree(int n, T val = {}) : n(n), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans += nodes[i];
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] += val;
    }
  }
};

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  vector<array<Int, 2>> q(m);
  vector<int> idx(n + 1, -1), nxt(n, -1), prv(n, -1), bad(n);
  for (int i = 0; i < n; i++) { // O(n)
    auto &j = idx[a[i]];
    if (j >= 0 && j + 1 < i) {
      nxt[j] = i;
      prv[i] = j;
    }
    j = i;
  }
  FenTree<int> pref(n);
  for (int i = 0, j = 1; i < n; j++) { // O(n*log n)
    if (j == n) {
      for (; i < j; i++) {
        bad[i] = j;
      }
    } else if (prv[j] >= i) {
      pref.update(prv[j], 1);
      pref.update(j, -1);
      while (pref.query(j - 1) != pref.query(prv[j])) {
        if (nxt[i] >= 0 && nxt[i] <= j) {
          pref.update(i, -1);
          pref.update(nxt[i], 1);
        }
        bad[i] = j;
        i++;
      }
    }
  }
  for (auto &&[l, r] : q) { // O(m)
    println(bad[l - 1] < r ? "NO" : "YES");
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
