/**
 * https://codeforces.com/contest/1984/submission/283841996
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
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
using Mint = Mod<u32, 998244353u>;

struct Fact : vector<Mint> {
  Fact() : vector<Mint>(1, 1) {}
  Mint operator[](int n) { // O(1) amortized (use reserve if necessary)
    while (size() <= n) {
      push_back(back() * size());
    }
    return vector<Mint>::operator[](n);
  }
};

template <typename T = int> struct Point {
  T x, y;
  Point &operator+=(const Point &p) { return x += p.x, y += p.y, *this; }
  Point &operator-=(const Point &p) { return x -= p.x, y -= p.y, *this; }
  Point &operator*=(T scale) { return x *= scale, y *= scale, *this; }
  Point &operator/=(T scale) { return x /= scale, y /= scale, *this; }
  Point operator+(const Point &p) const { return Point(x, y) += p; }
  Point operator-(const Point &p) const { return Point(x, y) -= p; }
  Point operator*(T scale) const { return Point(x, y) *= scale; }
  Point operator/(T scale) const { return Point(x, y) /= scale; }
  Point operator-() const { return {-x, -y}; } // reflect about y=-x
  Point reflect() const { return {y, x}; }     // reflect about y=x
  Point rotate() const { return {-y, x}; }     // rotate 90 degrees
  Point rotate(T rad) const {
    auto s = sin(rad), c = cos(rad);
    return {x * c - y * s, x * s + y * c};
  }
  Point unit() const { return *this / norm(); }
  Point normal() const { return rotate().unit(); }
  auto cross(const Point<T> &p) const { return x * p.y - y * p.x; }
  auto dot(const Point<T> &p) const { return x * p.x + y * p.y; }
  auto norm2() const { return dot(*this); }
  auto norm() const { return sqrt(norm2()); }
  auto slope() const { return y / double(x); }
  auto angle() const { return atan2(y, x); }
  auto operator<=>(const Point &p) const { return tie(x, y) <=> tie(p.x, p.y); }
};

int sign(auto x) { return (x > 0) - (x < 0); };

template <typename T = int> struct Circle {
  T r;
  Point<T> c;
  auto area() const { return numbers::pi * r * r; }
  auto perim() const { return numbers::pi * r * 2; }
  auto dist(const Point<T> &p) const { return r - (p - c).norm(); }
  auto side(const Point<T> &p) const { return sign(r * r - (p - c).norm2()); }
};

template <typename T = int> struct Triangle {
  Point<T> a, b, c;
  auto area() const {
    return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0;
  }
  auto perim() const {
    return (a - b).norm() + (b - c).norm() + (c - a).norm();
  }
  auto orient() const { return (b - a).cross(c - a); }
  auto side(const Point<T> &p) const {
    auto s1 = sign((a - b).cross(p - b));
    auto s2 = sign((b - c).cross(p - c));
    auto s3 = sign((c - a).cross(p - a));
    auto sum = abs(s1 + s2 + s3);
    return sum >= 2 ? sum - 2 : -!!(s1 * s2 * s3);
  }
  auto circle() const {
    auto v1 = b - a, v2 = c - a;
    i64 n1 = v1.norm2(), n2 = v2.norm2();
    auto ux = v2.y * n1 - v1.y * n2;
    auto uy = v1.x * n2 - v2.x * n1;
    auto u = Point<double>(ux, uy) / (2.0 * v1.cross(v2));
    return Circle<double>(u.norm(), u + Point<double>(a.x, a.y));
  }
  bool circum(const Point<T> &p) const {
    auto a1 = a - p, b1 = b - p, c1 = c - p;
    auto x = (i64)a1.norm2() * b1.cross(c1);
    auto y = (i64)b1.norm2() * c1.cross(a1);
    auto z = (i64)c1.norm2() * a1.cross(b1);
    return (x + y + z) * sign(orient()) >= 0;
  }
};

template <typename T> struct Polygon : vector<Point<T>> {
  using vector<Point<T>>::vector;
};

struct Hull : vector<int> {
  template <typename T> Hull(const Polygon<T> &p) : vector<int>(p.size()) {
    assert(size() > 2);
    auto cmp1 = [&](int i, int j) { return p[i].reflect() < p[j].reflect(); };
    auto cmp2 = [&](int i, int j) {
      auto r = (p[i] - p[front()]).cross(p[j] - p[front()]);
      return r > 0 || (r == 0 && p[i].x < p[j].x);
    };
    iota(begin(), end(), 0);
    ::swap(front(), *min_element(begin(), end(), cmp1));
    sort(begin() + 1, end(), cmp2);
    auto i = begin() + 3;
    for (auto j = i; j != end(); *i++ = *j++) {
      for (; (p[*(i - 1)] - p[*(i - 2)]).cross(p[*j] - p[*(i - 2)]) < 0; i--)
        ;
    }
    resize(i - begin());
  }
};

Fact fact;

void solve(int t) {
  Int n;
  Polygon<Int> p(n);
  Hull hull(p); // O(n*log n)
  int m = hull.size();
  int p0 = ranges::find(hull, 0) - hull.begin();
  int p1 = ranges::find(hull, 1) - hull.begin();
  if (p0 == m || p1 == m) {
    println(0);
    return;
  }
  auto chk = [&](int i, int j, int k) {
    auto &a = p[hull[i]];
    auto &b = p[hull[j]];
    auto &c = p[hull[k]];
    Triangle tri(a, b, c);
    for (int l = 0; l < m; l++) {
      if (l != i && l != j && l != k) {
        if (!tri.circum(p[hull[l]])) {
          return false;
        }
      }
    }
    return true;
  };
  Mint ans = 1;
  auto f = [&](auto &self, int i, int j) -> int { // O(n*log n) / O(n^2)
    for (int k = (i + 1) % m; k != j; k = (k + 1) % m) {
      if (chk(i, j, k)) {
        auto l = self(self, i, k);
        auto r = self(self, k, j);
        auto s = 1 + l + r;
        return ans *= s, s;
      }
    }
    return 0;
  };
  auto s0 = f(f, p0, p1);
  auto s1 = f(f, p1, p0);
  ans = s0 || s1 ? fact[m - 2] / ans : Mint(0);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
