/**
 * https://codeforces.com/contest/1993/submission/277067839
 *
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

template <typename T> T invmod(T x, T m) { // O(log^2 m) / x and m are coprime
  return x < 0   ? invmod(x % m + m, m)
         : x > 1 ? m - invmod(m % x, x) * 1ll * m / x
                 : 1;
} // https://codeforces.com/blog/entry/23365

array<int, 3> normalize(int dx, int w) { // O(log^2 w)
  auto g = gcd(dx, w);
  auto u = invmod(dx / g, w /= g);
  return {g, w, u};
};

void solve(int t) { // O(n + log^2 max(w,h))
  Int n;
  I64 k;
  Int w, h;
  Str s;
  vector<array<int, 2>> pos(n);
  for (int i = 0, x = 0, y = 0; i < n; i++) { // O(n)
    x += (s[i] == 'L') - (s[i] == 'R');
    y += (s[i] == 'U') - (s[i] == 'D');
    pos[i] = {x % (2 * w), y % (2 * h)};
  }
  auto [dx, dy] = pos[n - 1];
  auto [gx, mx, ux] = normalize(-dx, 2 * w); // O(log^2 w)
  auto [gy, my, uy] = normalize(-dy, 2 * h); // O(log^2 h)
  auto [g, mmx, umx] = normalize(mx, my);    // O(log^2 h)
  i64 ans = 0, l = lcm<i64>(mx, my);
  for (auto &[x, y] : pos) {          // O(n)
    if (x % gx == 0 && y % gy == 0) { // a solution exists for the CRT
      int ax = x / gx * i64(ux) % mx; // i = ax + b*mx (mod mx), for b >= 0
      int ay = y / gy * i64(uy) % my; // i = ay + b*my (mod my), for b >= 0
      int bx = (ay - ax) % my;        // modified CRT
      if (bx % g == 0) {              // a solution exists for the modified CRT
        int b = bx / g * i64(umx) % mmx; // b + z*l, for z >= 0
        i64 a = ax + i64(b) * mx;        // i = ax + (b + z*l)*mx, for z >= 0
        if (a < 0) {
          a += l;
        }
        if (k > a) {
          ans += 1 + (k - 1 - a) / l; // count of i in [0,k)
        }
      }
    }
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
