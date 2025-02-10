/**
 * https://codeforces.com/contest/2065/submission/305415421
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t; // available on 64-bit targets

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
  Mod pow(auto y) const { // O(log y) | 0^(-inf,0] -> 1
    Mod ans(1), base(*this);
    for (auto e = y < 0 ? ~y + u128(1) : +y; e; e >>= 1, base *= base) {
      e & 1 ? ans *= base : ans;
    }
    return y < 0 ? Mod(1) /= ans : ans;
  }
};
using Mint = Mod<int, 998244353>;

struct Pow2 : vector<Mint> {
  Pow2(int n) : vector<Mint>(n + 1, 1) { // O(n)
    for (int i = 0; i < n; i++) {
      (*this)[i + 1] = (*this)[i] * 2;
    }
  }
};

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
};

void solve(int t) {
  String s;
  int n = s.size();
  Int q;
  vector<Int> v(q);
  Pow2 pow2(n);
  array before = {FenTree<Mint>(n, plus{}), FenTree<Mint>(n, plus{})};
  array after = {FenTree<Mint>(n, plus{}), FenTree<Mint>(n, plus{})};
  auto upd = [&](int i, bool add) { // O(log n)
    auto b = s[i] - '0';
    before[b].update(i, add ? pow2[i] : -pow2[i]);
    after[b].update(i, add ? pow2[n - i - 1] : -pow2[n - i - 1]);
  };
  auto get = [&](int i, bool single) { // O(log n)
    auto b = 1 - s[i] + '0';
    return (single ? Mint() : before[b].query(i - 1) * pow2[n - i - 1]) +
           pow2[i] * (after[b].query(n - 1) - after[b].query(i));
  };
  for (int i = 0; i < n; i++) { // O(n*log n)
    upd(i, true);
  }
  Mint acc = pow2[n] - 1;
  for (int i = 0; i < n; i++) { // O(n*log n)
    acc += get(i, true);
  }
  auto flip = [&](int i) { // O(log n)
    acc -= get(i, false);
    upd(i, false);
    s[i] = '1' - s[i] + '0';
    upd(i, true);
    acc += get(i, false);
  };
  vector<int> ans(q);
  for (int i = 0; i < q; i++) { // O(q*log n)
    flip(v[i] - 1);
    ans[i] = acc;
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
