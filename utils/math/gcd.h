/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Absolute and Reverse modulus (works for negative numbers)
 */
constexpr auto absmod(auto x, auto m) { return (m + x % m) % m; };
constexpr auto revmod(auto x, auto m) { return (m - x % m) % m; };

/**
 * Extended Euclid's algorithm
 */
template <typename T> array<T, 3> exgcd(T m, T n) { // O(log^2 max(m,n))
  T a = 0, b = 1, u = 1, v = 0;
  while (n) {
    T q = m / n;
    m -= q * n, swap(m, n); // (m, n) = (n, m - q * n)
    u -= q * a, swap(u, a); // (u, a) = (a, u - q * a)
    v -= q * b, swap(v, b); // (v, b) = (b, v - q * b)
  }
  return {u, v, m}; // u*m + v*n == gcd(m,n)
}

/**
 * Modular Inverse for non-coprime numbers
 */
template <typename T> array<T, 3> gcdinvmod(T x, T m) { // O(log^2 m)
  auto [u, v, d] = exgcd(x, m);
  return {d, u, m / d}; // u may be negative
};

/**
 * Linear Diophantine equation
 */
template <typename T> array<T, 5> diophantine(T a, T b, T c) {
  auto [s, t, d] = exgcd(a, b);
  if (c % d) {
    return {};
  }
  auto u = a / d, v = b / d;
  auto x = c / d * 1ll * s, y = c / d * 1ll * t, k = x / v;
  return {true, T(x - k * v), T(y + k * u), u, v}; // adjusted for x % v
}

/**
 * Modular Multiplicative Inverse
 */
template <typename T> T invmod(T x, T m) { // O(log^2 m) / x and m are coprime
  return x < 0   ? invmod(x % m + m, m)
         : x > 1 ? m - invmod(m % x, x) * 1ll * m / x
                 : 1;
} // https://codeforces.com/blog/entry/23365
