/**
 * https://codeforces.com/contest/1984/submission/276990113
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

template <typename T> struct Mod {
  constexpr static T _def = 998244353;
  T x, m;
  operator T() const { return x; }
  void set(i64 y) { x = (y %= m) < 0 ? y + m : y; };
  Mod(i64 x = 0, T m = _def) : m(m) { set(x); }
  Mod operator+(auto y) const { return Mod(x, m) += y; }
  Mod operator-(auto y) const { return Mod(x, m) -= y; }
  Mod operator*(auto y) const { return Mod(x, m) *= y; }
  Mod operator/(auto y) const { return Mod(x, m) /= y; }
  Mod &operator+=(i64 y) { return set(x + y), *this; }
  Mod &operator-=(i64 y) { return set(x - y), *this; }
  Mod &operator*=(i64 y) { return set(x * y), *this; }
  Mod &operator/=(i64 y) { // O(log^2 m) / y and m must be coprime
    i64 u = 0, v = 1, d = m;
    while (y) {
      auto q = d / y;
      d -= q * y, swap(d, y); // (d, y) = (y, d - q * y)
      u -= q * v, swap(u, v); // (u, v) = (v, u - q * v)
    }
    assert(d == 1); // u*y == 1 (mod m)
    return operator*=(u);
  }
  Mod pow(auto y) const { // O(log y) / 0^0 -> 1
    Mod ans(1, m), base(x, m);
    for (; y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<int>;

void solve(int t) {
  Int n, m;
  Str s;
  s.assign('P' + s + 'S');
  vector<I64> b(1, 0);
  b.resize(n + 1);
  b.push_back(0);
  auto f = [&](i64 sum) {
    array<Mint, 2> dp = {1, 0};
    for (int i = 1; i < n + 2; i++) {
      array<Mint, 2> dp1 = {0, 0};
      i64 x = b[i - 1] + b[i] - sum;
      i64 y = b[i - 1] - b[i];
      i64 value[2][2] = {{y, x}, {x, y}};
      i64 limit[2][2] = {{m, 0}, {2 * m, m}};
      bool check[2] = {s[i] != 'S', s[i] != 'P'};
      for (int j = 0; j < 2; j++) {   // prev
        for (int k = 0; k < 2; k++) { // curr
          if (check[k]) {
            if (abs(value[j][k]) <= limit[j][k]) {
              dp1[k] += dp[j];
            }
          }
        }
      }
      dp = dp1;
      if (!dp[0] && !dp[1]) {
        break;
      }
    }
    return dp[0] += dp[1];
  };
  Mint ans = 0;
  set<i64> sums;
  i64 nm = i64(n) * m;
  for (int i = 1; i < n + 2; i++) {
    auto sum = b[i] + b[i - 1];
    if (abs(sum) <= nm && sums.insert(sum).second) {
      ans += f(sum);
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
