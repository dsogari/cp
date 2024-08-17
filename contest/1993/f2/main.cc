/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
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
using I64 = Num<i64>;

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T> array<T, 3> exgcd(T m, T n) { // O(log^2 max(m,n))
  T u = 1, v = 0;
  for (T a = 0, b = 1; n;) {
    T q = m / n;
    m -= q * n, swap(m, n); // (m, n) = (n, m - q * n)
    u -= q * a, swap(u, a); // (u, a) = (a, u - q * a)
    v -= q * b, swap(v, b); // (v, b) = (b, v - q * b)
  }
  return {u, v, m}; // u*m + v*n == gcd(m,n)
}

void solve(int t) { // O(n*log^2 max(w, h))
  I64 n, k, w, h;
  Str s;
  int dx = 0, dy = 0;
  for (int i = 0; i < n; i++) { // O(n)
    dx += (s[i] == 'L') - (s[i] == 'R');
    dy += (s[i] == 'U') - (s[i] == 'D');
  }
  auto gx = gcd<int, int>(dx, 2 * w);
  auto gy = gcd<int, int>(dy, 2 * h);
  auto w1 = 2 * w / gx, h1 = 2 * h / gy;
  auto [ux, _x, mx] = exgcd<int>(dx / gx, w1);
  auto [uy, _y, my] = exgcd<int>(dy / gy, h1);
  assert(mx == 1 && my == 1);
  auto f = [&](int x, int y) {
    if (x % gx == 0 && y % gy == 0) { // a solution exists for the CRT
      // count of i in [0,k-1] such that i == ax (mod w1) == ay (mod h1)
      auto ax = (-x / gx * ux) % w1; // i = cx + z*w1, for z >= 0
      auto ay = (-y / gy * uy) % h1;
    }
    return 0;
  };
  i64 ans = 0;
  for (int i = 0, x = 0, y = 0; i < n; i++) { // O(n*log^2 max(w, h))
    x += (s[i] == 'L') - (s[i] == 'R');
    y += (s[i] == 'U') - (s[i] == 'D');
    ans += f(x, y);
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
