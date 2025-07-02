/**
 * https://codeforces.com/contest/2123/submission/327121520
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  FenTree(int n, T val = {}) : n(n), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) ans += nodes[i];
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) nodes[i] += val;
  }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  vector<int> freq(n + 1), ans(n + 1, 1);
  FenTree<int> fen(n + 1);
  for (auto &&x : a) {
    freq[x]++;
  }
  int mex = ranges::find(freq, 0) - freq.begin();
  for (int i = 0, k = n - 1; k > 0; k--) {
    while (i < mex && n - i >= k) {
      fen.update(freq[i], 1);
      i++;
    }
    ans[k] = fen.query(k) + (n - mex >= k);
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
