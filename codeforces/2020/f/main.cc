/**
 * https://codeforces.com/contest/2020/submission/284387751
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

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

template <typename T, auto M>
  requires unsigned_integral<T>
struct Mod {
  using U = conditional<is_same<T, u64>::value, u128, u64>::type;
  static T inv(T x, U m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  static T norm(T x) { return rotl(x, 1) & 1 ? x + M : x < M ? x : x - M; }
  T x;
  Mod() : x(0) {}
  Mod(i64 y) : x(norm(y % i64(M))) {}
  operator T() const { return x; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return x = norm(x + rhs.x), *this; }
  Mod &operator-=(Mod rhs) { return x = norm(x - rhs.x), *this; }
  Mod &operator*=(Mod rhs) { return x = U(x) * rhs.x % M, *this; }
  Mod &operator/=(Mod rhs) { return *this *= inv(rhs.x, M); }
  Mod pow(i64 y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1), base(y < 0 ? inv(x, M) : x);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<u32, 1000000007u>;

struct Binom {
  vector<Mint> fac, inv;
  Binom() : fac(1, 1), inv(1, 1) {}
  Mint permute(int n) { return update(n), fac.at(n); }               // O(1)
  Mint commute(int n) { return update(n), inv.at(n); }               // O(1)
  Mint invert(int n) { return arrange(n - 1, -1); }                  // O(1)
  Mint pascald(int n, int k) { return combine(n + k, k); }           // O(1)
  Mint arrange(int n, int k) { return permute(n) * commute(n - k); } // O(1)
  Mint combine(int n, int k) { return arrange(n, k) * commute(k); }  // O(1)
  void reserve(int n) { fac.reserve(n), inv.reserve(n); }            // O(n)
  void update(int n) { // O(1) amortized
    int s = fac.size();
    if (s <= n) {
      fac.resize(n + 1);
      inv.resize(n + 1);
      for (int i = s; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
      }
      inv[n] = Mint(1) / fac[n];
      for (int i = n; i > s; i--) {
        inv[i - 1] = inv[i] * i;
      }
    }
  }
} binom;

constexpr struct SmallPrimes : array<u16, 6542> { // ~13KB
  constexpr SmallPrimes() {                       // O(N*log log N) = O(2^18)
    array<bool, 1 << 16> vis = {};
    for (int i = 2, cnt = 0; i < vis.size(); i++) {
      if (!vis[i]) {
        (*this)[cnt++] = i;
        for (int j = 2 * i; j < vis.size(); j += i) {
          vis[j] = true;
        }
      }
    }
  }
} primes;

struct Lucy : vector<int> {
  int n, s, m;
  Lucy(int n, auto &&f) : n(n), s(sqrt(n)), m(2 * this->s) { // O(n^0.75)
    vector<int> v(m);
    for (int i = 0; i < m; i++) {
      v[i] = i < s ? i + 1 : n / (m - i);
      push_back(f(v[i]));
    }
    for (int p = 2; p <= s; p++) {
      if ((*this)[p - 1] != (*this)[p - 2]) { // p is prime
        for (int i = m - 1; i >= 0 && p * p <= v[i]; i--) {
          (*this)[i] -= get(v[i] / p) - (*this)[p - 2];
        }
      }
    }
  }
  int get(int x) const { return (*this)[x <= s ? x - 1 : m - n / x]; }; // O(1)
};

Mint black(int n, auto &&unit, auto &&sum) { // O(n)
  Lucy lucy(n, [](int x) { return x - 1; });
  auto dfs = [&](auto &self, int x, int i, int e, Mint prod) -> Mint {
    auto cur = prod * unit(i, e); // f(x*p^e)
    auto ans = cur;
    for (int j = i; j < primes.size(); j++) {
      auto y = u64(x) * primes[j]; // next number
      if (y * primes[j] > n) {
        ans += cur * sum(max(i + 1, j), lucy.get(n / x) - 1);
        if (j == i && y <= n) {
          ans += prod * unit(i, e + 1);
        }
        break;
      }
      ans += self(self, y, j, j == i ? e + 1 : 1, j == i ? prod : cur);
    }
    return ans;
  };
  return dfs(dfs, 1, 0, 0, 1);
}

void solve(int t) {
  Int n, k, d;
  int m = bit_width<unsigned>(n); // maximum number of factors
  binom.reserve(m * k + d + 1);   // avoid memory reallocations
  vector<Mint> memo(m + 1);
  for (int i = m; i >= 0; i--) { // O(log n)
    memo[i] = binom.pascald(i * k, d);
  }
  debug(memo);
  auto unit = [&](int i, int e) { return memo[e]; };
  auto sum = [&](int l, int r) { return memo[1] * max(0, r - l + 1); };
  auto ans = black(n, unit, sum);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
