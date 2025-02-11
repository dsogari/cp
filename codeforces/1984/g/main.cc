/**
 * https://codeforces.com/contest/1984/submission/285967166
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
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

template <typename T> struct Barrett {
  static inline conditional_t<sizeof(T) <= 4, u64, u128> m, u;
  static void set(T y) { m = y, u = -1 / m; } // u = 2^(16*sizeof(T))/m
  operator T() const { return m; }
  static u64 div(u128 x) requires(sizeof(T) <= 4) { return x * u >> 64; }
  static u128 div(u128 x) requires(sizeof(T) > 4) {
    u128 xl = u64(x), ul = u64(u), xh = x >> 64, uh = u >> 64;
    auto a = xl * ul, b = xl * uh, c = ul * xh, d = xh * uh;
    return d + (b >> 64) + (c >> 64) + (((a >> 64) + u64(b) + u64(c)) >> 64);
  }
  friend auto operator/(auto x, Barrett) requires(sizeof(x) <= sizeof(u)) {
    auto q = x < 0 ? ~div(~x + u128(1)) : div(x);
    return decltype(x)(q + (x < 0 ? x > q * m : x >= (q + 1) * m));
  }
  friend auto operator%(auto x, Barrett) requires(sizeof(x) <= sizeof(u)) {
    auto q = x < 0 ? ~div(~x + u128(1)) : div(x);
    return x -= q * m, decltype(x)(x < 0 || x < m ? x : x - m);
  }
};

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
using Mint = Mod<int, Barrett<int>{}>;

int invcount(auto &&f, int s, int e) { // [s, e) O(n^2)
  int ans = 0;
  for (int i = s; i < e; i++) {
    for (int j = i + 1; j < e; j++) {
      ans += f(j, i);
    }
  }
  return ans;
}

int cyclicshift(auto &&f, int s, int e) { // [s, e) O(n)
  int ans = 0;
  for (int i = s + 1; i < e; i++) {
    if (f(i, i - 1)) {
      if (ans) {
        return -1; // array must contain at most one such inversion
      }
      ans = i;
    }
  }
  return ans && s < e - 2 && f(s, e - 1) ? -1 : ans;
}

void solve(int t) {
  Int n;
  vector<Int> a(n);
  vector<array<int, 2>> ops;
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  auto shift = cyclicshift(cmp, 0, n);
  int ans = n;
  if (shift > 0) {
    for (ans--; shift < n; shift++) {
      ops.push_back({1, 2});
    }
  } else if (shift < 0) {
    auto inv = invcount(cmp, 0, n);
    ans -= 2;
    if (n % 2 == 0) {
      ans -= inv % 2;
      int m = n - ans;
      auto it = find(a.begin(), a.end(), n);
      int i = it - a.begin() + 1, k = (n - i) % m;
      if (k > 0) {
        int j = max(0, i - ans);
        ops.push_back({j + 1, j + 1 + k});
        auto it1 = a.begin() + j;
        ranges::rotate(it1, it1 + ans, it1 + ans + k);
        it += k;
      }
      for (int j = 0; j < (n - i) / m; j++) {
        ops.push_back({1, m + 1});
      }
      ranges::rotate(a.begin(), it + 1, a.end());
      n -= inv % 2;
    }
    const array<int, 2> fwd1{2, 1}, bwd1{1, 2}, fwd2{3, 1}, bwd2{1, 3};
    Barrett<int>::set(n);
    Mint c = n - 1;
    auto findpos = [&](int i, int d) {
      int k = 0;
      for (; a[c - (k - d)] != i && a[c + (k + d)] != i && k < n; k += 2);
      return a[c - (k - d)] == i ? make_pair(-k, bwd2) : make_pair(k, fwd2);
    };
    auto f = [&](int i, bool move) {
      auto [dist, op] = findpos(i, 0);
      auto fix = abs(dist) == n;
      if (fix) {
        tie(dist, op) = findpos(i, -1);
      }
      c += dist;
      for (int j = abs(dist); j > 0; j -= 2) {
        ops.push_back(op);
      }
      if (move) {
        if (fix) {
          for (; a[c] != i + 1; c += 1) {
            swap(a[c], a[c - 1]);
            ops.push_back(bwd1);
            ops.push_back(fwd2);
          }
        } else {
          for (; a[c + 1] != i + 1; c += 1) {
            swap(a[c + 1], a[c]);
            ops.push_back(fwd1);
          }
        }
      }
    };
    f(n, false);
    for (int i = n - 1; i > 1; i--) {
      for (int j = 1; a[c - j] == i && i > 1; j++, i--);
      if (i > 1) {
        f(i, true);
      }
    }
    f(n, false);
  }
  println(ans);
  println(ops.size());
  println(ops);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
