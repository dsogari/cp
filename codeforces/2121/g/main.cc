/**
 * https://codeforces.com/contest/2121/submission/325209223
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

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
  Str s;
  vector<int> suff(n + 1);
  for (int i = n - 1; i >= 0; i--) {
    suff[i] += suff[i + 1] + (s[i] == '0' ? 1 : -1);
  }
  FenTree<int> fen(2 * n + 1);
  i64 ans = 0, acc = 0;
  for (int i = 0; i < n; i++) {
    fen.update(suff[i] + n, 1);
    if (s[i] == '0') {
      acc += fen.query(2 * n) - fen.query(suff[i] + n - 1);
    } else {
      acc += fen.query(suff[i] + n);
    }
    ans += acc;
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
