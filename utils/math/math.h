/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Element-wise assigment sum of static array
 */
template <typename T, size_t N>
array<T, N> &operator+=(array<T, N> &lhs, const array<T, N> &rhs) { // O(N)
  for (int i = 0; i < N; i++) {
    lhs[i] += rhs[i];
  }
  return lhs;
}

/**
 * Element-wise sum of static array
 */
template <typename T, size_t N>
array<T, N> operator+(const array<T, N> &lhs, const array<T, N> &rhs) { // O(N)
  array<T, N> ans;
  for (int i = 0; i < N; i++) {
    ans[i] = lhs[i] + rhs[i];
  }
  return ans;
}

/**
 * Bhaskara formula
 */
constexpr auto bhaskara(auto a, auto b, auto c) { // O(log n)
  return (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
}

/**
 * Sum of arithmetic progressions
 */
constexpr auto apsum(auto a, auto b, auto n) { return n * (a + b) / 2; } // O(1)

/**
 * Sum of geometric progressions
 */
constexpr auto gpsum(auto a, auto r, auto n) { // O(log n)
  return a * (1 - pow(r, n)) / (1 - r);
}

/**
 * Check if two intervals cross each other
 */
constexpr int crosses(int l1, int r1, int l2, int r2) {
  return (l1 < l2 && l2 < r1 && r1 < r2) - (l2 < l1 && l1 < r2 && r2 < r1);
}

/**
 * Number of times that y divides x evenly
 */
int countdiv(int x, int y) { // O(log x)
  assert(y > 1);
  int c = 0;
  for (div_t d = {}; !d.rem && x > 1; c += !d.rem) {
    d = div(x, y);
    x = d.quot;
  }
  return c;
}

/**
 * Choices satisfying equality x + y == m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices_eq(int a1, int a2, int b1, int b2, i64 m) { // O(1)
  assert(a1 <= a2 && b1 <= b2);
  auto d1 = m - a1, d2 = m - a2;
  return b1 <= d1 && b2 >= d2 ? min<i64>(b2, d1) - max<i64>(b1, d2) + 1 : 0;
}

/**
 * Choices satisfying inequality x + y <= m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices_lte(int a1, int a2, int b1, int b2, i64 m) { // O(a2-a1)
  assert(a1 <= a2 && b1 <= b2);
  i64 ans = 0;
  for (int i = min<i64>(a2, m - b1); i >= a1; i--) {
    ans += min<i64>(b2, m - i) - b1 + 1;
  }
  return ans;
}

/**
 * Maximum sum satisfying inequality a * x + b * y <= m, for x <= ca and y <= cb
 */
i64 maxsum(int a, int ca, int b, int cb, i64 m) { // O(1)
  assert(a > 0 && a < b);
  auto ua = min<i64>(ca, m / a);
  auto ub = min<i64>(cb, (m - ua * a) / b);
  auto ra = min<i64>({ua, cb - ub, (m - ua * a - ub * b) / (b - a)});
  return (ua - ra) * a + (ub + ra) * b;
}

// Utility functions
// minmax

// Bit functions
// rotl: Rotate `x` to the left by `s` bits.
// rotr: Rotate `x` to the right by `s` bits.
// countl_zero: number of contiguous zero bits, starting from the highest bit.
// countl_one: number of contiguous one bits, starting from the highest bit.
// countr_zero: number of contiguous zero bits, starting from the lowest bit.
// countr_one: number of contiguous one bits, starting from the lowest bit.
// popcount: number of bits set in `x`.
// has_single_bit: whether `x` is a power of two.
// bit_ceil: smallest power-of-two not less than `x`.
// bit_floor: largest power-of-two not greater than `x`.
// bit_width: smallest integer greater than the base-2 logarithm of `x`.
