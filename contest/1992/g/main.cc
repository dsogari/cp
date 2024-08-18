/**
 * https://codeforces.com/contest/1992/submission/277069008
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

template <typename T> struct Mod {
  constexpr static T _def = 1000000007; // 998244353;
  static i64 inv(i64 x, i64 m) {        // O(log^2 m) / x and m must be coprime
    return x < 0 ? inv(x % m + m, m) : x > 1 ? m - inv(m % x, x) * m / x : 1;
  } // https://codeforces.com/blog/entry/23365
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
  Mod &operator/=(i64 y) { return *this *= inv(y, m); }
  Mod pow(auto y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1, m), base(y < 0 ? inv(x, m) : x, m);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<int>;

template <typename T> struct Fac : vector<Mod<T>> {
  Fac(T m = Mod<T>::_def) : vector<Mod<T>>(1, {1, m}) {}
  Mod<T> operator[](int n) {
    while (this->size() <= n) {
      this->push_back(this->back() * this->size());
    }
    return vector<Mod<T>>::operator[](n);
  }
};

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

Bin<int> bin;

void solve(int t) {
  Int n;
  Mint ans = 2 * (n + 1); // empty and n-ary sets
  for (int i = 1; 2 * i < n; i++) {
    for (int j = 0; j <= i; j++) {
      int m = j + i + 1; // result of mex
      ans += bin(m - 1, j) * bin(n - m, i - j) * m;
    }
  }
  for (int i = (n + 1) / 2; i < n; i++) {
    ans += bin(n, i) * (2 * i + 1);
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
