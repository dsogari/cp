/**
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
using u128 = __uint128_t; // available on 64-bit targets

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
using Int = Number<int>;

template <typename T, auto M> struct Mod {
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  static V inv(V x, V m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  make_unsigned_t<T> x;
  Mod() : x(0) {}
  Mod(auto y) : x(y % M) { x >= M ? x += M : x; }
  operator T() const { return x; }
  Mod operator-() const { return Mod() -= *this; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return (x += rhs.x) >= M ? x -= M : x, *this; }
  Mod &operator-=(Mod rhs) { return (x -= rhs.x) >= M ? x += M : x, *this; }
  Mod &operator*=(Mod rhs) { return x = x * V(rhs.x) % M, *this; }
  Mod &operator/=(Mod rhs) { return x = x * inv(rhs.x, M) % M, *this; }
};
using Mint = Mod<int, 998244353>;

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

struct Pow : vector<Mint> {
  Pow(int n, Mint base) : vector<Mint>(n + 1, 1) { // O(n)
    for (int i = 0; i < n; i++) {
      (*this)[i + 1] = (*this)[i] * base;
    }
  }
};

void solve(int t) {
  Int n;
  Pow pow2(n, 2), invpow2(n, Mint(1) / 2);
  vector<array<Int, 2>> a(n);
  vector<int> left, right;
  for (auto &&[l, r] : a) {
    left.push_back(l - 1);
    right.push_back(r - 1);
  }
  ranges::sort(left);
  ranges::sort(right);
  FenTree<Mint> fen1(n), fen2(n);
  for (int i = 0, j = 0; i < n; i++) {
    if (i == n - 1 || right[i] != right[i + 1]) {
      auto c = pow2[n - j - 1] * (i + 1 - j);
      fen1.update(right[i], c);
      fen2.update(right[i], c * right[i]);
      j = i + 1;
    }
  }
  Mint ans;
  for (int i = 1; i < n; i++) {
    auto l = left[i];
    auto c = fen1.query(l) * l - fen2.query(l);
    c *= invpow2[n - i];
    ans += c;
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
