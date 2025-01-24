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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

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

struct Binom {
  vector<Mint> fac, inv;
  Binom() : fac(1, 1), inv(1, 1) {}
  Mint permute(int n) { return update(n), fac.at(n); }               // O(1)
  Mint commute(int n) { return update(n), inv.at(n); }               // O(1)
  Mint invert(int n) { return arrange(n - 1, -1); }                  // O(1)
  Mint pascald(int n, int k) { return combine(n + k, k); }           // O(1)
  Mint catalan(int n) { return combine(2 * n, n) * invert(n + 1); }  // O(1)
  Mint arrange(int n, int k) { return permute(n) * commute(n - k); } // O(1)
  Mint combine(int n, int k) { return arrange(n, k) * commute(k); }  // O(1)
  void reserve(int n) { fac.reserve(n + 1), inv.reserve(n + 1); }    // O(n)
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

void solve(int t) {
  Int n;
  binom.reserve(n);
  vector<array<Int, 2>> a(n);
  vector<array<int, 2>> b(2 * n);
  vector<Mint> pow2(n + 1, 1), inv(n + 1, 1);
  for (int i = 0; i < n; i++) { // O(n)
    for (int j = 0; j < 2; j++) {
      b[2 * i + j] = {a[i][j], j};
    }
    pow2[i + 1] = pow2[i] * 2;
    inv[i + 1] /= i + 1;
  }
  ranges::sort(b); // O(n*log n)
  vector memo(n, vector<Mint>(1, 1));
  for (int x = 0; x < n; x++) { // O(n^2)
    for (int y = 1; y < n - x; y++) {
      memo[x].push_back(memo[x].back() * (x + y) * inv[2] * inv[y]);
    }
    for (int y = 1; y < n - x; y++) {
      memo[x][y] = memo[x][y] + memo[x][y - 1];
    }
  }
  Mint ans;
  int cl = n, cr = 0;
  for (auto [val, right] : b) { // O(n)
    if (right) {
      if (cl) {
        auto sum = memo[cr][cl - 1] * pow2[cl - 1];
        ans -= sum * val * pow2[n - 1 - cr - cl];
      }
      cr++;
    } else {
      cl--;
      if (cr) {
        auto sum = memo[cl][cr - 1] * pow2[cr - 1];
        ans += sum * val * pow2[n - 1 - cl - cr];
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
