/**
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T> struct Str : basic_string<T> {
  using basic_string<T>::basic_string;
  Str() { cin >> *this; }
};
using String = Str<char>;

template <typename T> struct Sparse {
  int k, n;
  vector<vector<T>> nodes;
  function<T(const T &, const T &)> f;
  Sparse(int n, auto &&f)
      : k(bit_width<unsigned>(n)), n(n), f(f), nodes(k, vector<T>(n)) {}
  T &operator[](int i) { return nodes[0][i]; } // O(1)
  void build() {                               // O(n*log n)
    for (int i = 0; i < k - 1; i++) {
      for (int j = 0; j + (1 << i) < n; j++) {
        nodes[i + 1][j] = f(nodes[i][j], nodes[i][j + (1 << i)]);
      }
    }
  }
  T query(int l, int r) const { // [l, r] O(1)
    _check(l, r);
    int i = bit_width<unsigned>(r - l + 1) - 1;
    return f(nodes[i][l], nodes[i][r - (1 << i) + 1]);
  }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

template <typename T> struct Min {
  T operator()(const T &lhs, const T &rhs) const { return min(lhs, rhs); }
};

template <typename T> struct Max {
  T operator()(const T &lhs, const T &rhs) const { return max(lhs, rhs); }
};

constexpr int maxn = 2 * ('z' - 'a') + 1;

void solve(int t) {
  Int n;
  String s;
  if (n % 2 == 0 || n > maxn) {
    return println("YES");
  }
  Sparse<char> sparsemin(n, Min<char>{});
  Sparse<char> sparsemax(n, Max<char>{});
  auto f = [&](int l, int r) { // O(1)
    auto [mn, mx] = minmax(s[l], s[r]);
    auto mid = sparsemax.query(l + 1, r - 1);
    if (mid < mn) {
      auto mnl = l == 0 ? 0 : sparsemin.query(0, l - 1);
      auto mnr = r == n - 1 ? 0 : sparsemin.query(r + 1, n - 1);
      auto mxl = max(s[l], l % 2 == 0 || mnl < s[l] ? 'z' : 'y');
      auto mxr = max(s[r], r % 2 == 0 || mnr < s[r] ? 'z' : 'y');
      return mx <= min(mxl, mxr);
    }
    return false;
  };
  for (int i = 0; i < n; i++) { // O(a)
    sparsemin[i] = s[i];
    sparsemax[i] = s[i];
  }
  sparsemin.build();            // O(a*log a)
  sparsemax.build();            // O(a*log a)
  for (int i = 0; i < n; i++) { // O(a^2)
    for (int j = i + 2; j < n; j += 2) {
      if (f(i, j)) {
        return println("YES");
      }
    }
  }
  return println("NO");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
