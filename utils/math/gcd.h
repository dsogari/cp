/**
 * (c) 2024 Diego Sogari
 */
#pragma once

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
    m = exchange(n, m - q * n);
    u = exchange(a, u - q * a);
    v = exchange(b, v - q * b);
  }
  return {u, v, m}; // u*m + v*n == gcd(m,n)
}

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
 * Modular Inverse for non-coprime arguments
 */
template <typename T> array<T, 3> gcdinvmod(T x, T m) { // O(log^2 m)
  auto [u, v, d] = exgcd(x, m);
  return {d, u, m / d}; // u may be negative
};

/**
 * Modular Inverse for positive coprime arguments (iterative)
 */
auto invmod_iter(auto x, auto m) -> decltype(m) { // O(log^2 m)
  auto a = exchange(x, 1);
  auto b = exchange(m, 0);
  for (; b; a = exchange(b, a % b)) {
    x = exchange(m, x - (a / b) * m);
  }
  return x < 0 || (m > 0 && x >= m) ? x + m : x;
}

/**
 * Modular Inverse for positive coprime arguments (recursive)
 * https://codeforces.com/blog/entry/23365
 */
auto invmod_rec(auto x, auto m) -> decltype(m) { // O(log^2 m)
  return x > 1 ? m - u128(1) * invmod_rec(m % x, x) * m / x : 1;
}
