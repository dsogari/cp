/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Modular integer
 * LLDB: type summary add --summary-string "${var.x}" -x "^Mod<"
 */
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
using Mint = Mod<int, 1000000007>;
// using Mint = Mod<int, 998244353>;
// using Mint = Mod<int, Barrett<int>{}>;

/**
 * Binary Exponentiation
 */
Mint mpow(Mint x, auto y) { // O(log y) | 0^(-inf,0] -> 1
  Mint ans = 1;
  for (auto e = y < 0 ? ~y + u128(1) : +y; e; e >>= 1, x *= x) {
    e & 1 ? ans *= x : ans;
  }
  return y < 0 ? Mint(1) /= ans : ans;
}

/**
 * Powers of Two
 */
struct Pow2 : vector<Mint> {
  Pow2(int n) : vector<Mint>(n + 1, 1) { // O(n)
    for (int i = 0; i < n; i++) {
      (*this)[i + 1] = (*this)[i] + (*this)[i];
    }
  }
};
