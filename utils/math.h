/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Modular integer
 */
template <typename T> struct Mod {
  constexpr static T _def = 1000000007; // 998244353;
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
using Mi64 = Mod<i64>;

/**
 * (Modular) Factorial
 */
template <typename T> struct Fac : vector<Mod<T>> {
  Fac(T m = Mod<T>::_def) : vector<Mod<T>>(1, {1, m}) {}
  Mod<T> operator[](int n) {
    while (this->size() <= n) {
      this->push_back(this->back() * this->size());
    }
    return vector<Mod<T>>::operator[](n);
  }
};

/**
 * (Modular) Binomial coefficient
 */
template <typename T> struct Bin : Fac<T> {
  vector<Mod<T>> inv;
  Mod<T> operator()(int n, int k) {
    if (k < 0 || k > n) {
      return this->front() * 0;
    }
    auto ans = (*this)[n];
    if (inv.size() <= n) {
      int s = inv.size();
      inv.resize(n + 1);
      inv[n] = Mod(1, ans.m) / ans;
      for (int i = n; i > s; i--) {
        inv[i - 1] = inv[i] * i;
      }
    }
    return ans * inv[k] * inv[n - k];
  }
};

/**
 * Chinese Remainder Theorem
 */
template <typename T> struct CRT : vector<Mod<T>> {
  using vector<Mod<T>>::vector;
  Mod<i64> operator()() const { // O(n*log^2 max(mi))
    i64 m = 1;
    for (const auto &ai : *this) {
      m *= ai.m;
    }
    Mod ans = {0, m};
    for (const auto &ai : *this) { // O(n*log^2 max(mi))
      auto Mi = Mod(m / ai.m, m);
      ans += Mi * (ai / Mi);
    }
    return ans;
  }
};

/**
 * Precomputed integer factors (Divisors)
 */
struct Div : vector<vector<int>> {
  Div(int n) : vector<vector<int>>(n + 1) { // O(n*log n)
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

/**
 * Uniform Distribution using Mersenne Twister engine
 */
struct Dist : uniform_int_distribution<int> {
  Dist(int s, int e) : uniform_int_distribution<int>(s, e) {}
  int operator()() {
    static random_device device;
    static mt19937 engine{device()};
    return uniform_int_distribution<int>::operator()(engine);
  }
};

/**
 * Array hashing function
 */
template <size_t N> struct ArrayHash {
  size_t operator()(const array<int, N> &a) const {
    size_t h = 0;
    for (auto e : a) {
      h ^= hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
  }
};

/**
 * Choices satisfying equality x + y == m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices_eq(int a1, int a2, int b1, int b2, i64 m) {
  assert(a1 <= a2 && b1 <= b2);
  auto d1 = m - a1, d2 = m - a2;
  return b1 <= d1 && b2 >= d2 ? min<i64>(b2, d1) - max<i64>(b1, d2) + 1 : 0;
}

/**
 * Choices satisfying inequality x + y <= m, for a1 <= x <= a2 and b1 <= y <= b2
 */
i64 choices_lte(int a1, int a2, int b1, int b2, i64 m) {
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
i64 maxsum(int a, int ca, int b, int cb, i64 m) {
  assert(a > 0 && a < b);
  auto ua = min<i64>(ca, m / a);
  auto ub = min<i64>(cb, (m - ua * a) / b);
  auto ra = min<i64>({ua, cb - ub, (m - ua * a - ub * b) / (b - a)});
  return (ua - ra) * a + (ub + ra) * b;
}

/**
 * Absolute and Reverse modulus (works for negative numbers)
 */
constexpr auto absmod(auto x, auto m) { return (m + x % m) % m; };
constexpr auto revmod(auto x, auto m) { return (m - x % m) % m; };

/**
 * Most/least significant set bits/next power of 2
 */
constexpr int lssb(unsigned x) { return countr_zero(x); }
constexpr int mssb(unsigned x) { return 31 - countl_zero(x); }
constexpr int nxp2(unsigned x) { return 1 << (1 + mssb(x - 1)); }

/**
 * Extended Euclid's algorithm
 */
template <typename T> array<T, 3> exgcd(T m, T n) { // O(log^2 max(m,n))
  T u = 1, v = 0, a = 0, b = 1;
  while (n) {
    T q = m / n;
    m -= q * n, swap(m, n); // (m, n) = (n, m - q * n)
    u -= q * a, swap(u, a); // (u, a) = (a, u - q * a)
    v -= q * b, swap(v, b); // (v, b) = (b, v - q * b)
  }
  return {u, v, m}; // u*m + v*n == gcd(m,n)
}

/**
 * Modular Multiplicative Inverse
 */
auto invmod(auto x, auto m) { // O(log^2 m) / x and m must be coprime
  decltype(m) u = 0, v = 1;
  while (x) {
    auto q = m / x;
    m -= q * x, swap(m, x); // (m, x) = (x, m - q * x)
    u -= q * v, swap(u, v); // (u, v) = (v, u - q * v)
  }
  assert(m == 1); // u*x == 1 (mod m)
  return u;
}
