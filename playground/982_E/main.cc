/**
 * https://codeforces.com/contest/982/submission/286193063
 *
 * (c) 2024 Diego Sogari
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

template <typename T> array<T, 3> exgcd(T m, T n) { // O(log^2 max(m,n))
  T a = 0, b = 1, u = 1, v = 0;
  while (n) {
    T q = m / n;
    m = exchange(n, m - q * n);
    u = exchange(a, u - q * a);
    v = exchange(b, v - q * b);
  }
  return {u, v, m}; // u*m + v*n == gcd(m,n)
}

template <typename T> array<T, 5> diophantine(T a, T b, T c) {
  auto [s, t, d] = exgcd(a, b);
  if (c % d) {
    return {};
  }
  auto u = a / d, v = b / d;
  auto x = c / d * 1ll * s, y = c / d * 1ll * t, k = x / v;
  return {true, T(x - k * v), T(y + k * u), u, v}; // adjusted for x % v
}

void solve(int t) { // O(log^2 max(n,m))
  Int n, m, xi, yi, vx, vy;
  if (!vx || !vy) {
    vx && (yi % m == 0)   ? println(vx > 0 ? +n : 0, yi)
    : vy && (xi % n == 0) ? println(xi, vy > 0 ? +m : 0)
                          : println(-1);
    return; // degenerate case
  }
  auto [ok, x, y, u, v] = diophantine(n * vy, -m * vx, xi * vy - yi * vx);
  if (!ok) {
    println(-1);
    return; // equation has no solution
  }
  auto c = (1ll * x * n - xi) / vx; // time to reach a pocket
  if (c <= 0) {
    x += v, y -= u; // adjustment to get the first c > 0
  }
  println((x & 1) * n, (y & 1) * m);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
#ifdef ONLINE_JUDGE
  Int t = 1;
#else
  Int t;
#endif
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
