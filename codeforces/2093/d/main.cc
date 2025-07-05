/**
 * https://codeforces.com/contest/2093/submission/327493930
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using I64 = Number<i64>;
using Str = String<char>;

struct Query {
  Str type;
  Int x = type == "->" ? Int() : Int(0);
  Int y = type == "->" ? Int() : Int(0);
  I64 d = type == "->" ? I64(0) : I64();
};

void solve(int t) {
  Int n, q;
  vector<Query> a(q);
  auto f1 = [&](int i, int j) { // O(n)
    i64 x = 0;
    for (int k = 0; k < n; k++, i >>= 1, j >>= 1) {
      if (i & 1 && j & 1) {
        x |= i64(1) << 2 * k;
      } else if (i & 1 && ~j & 1) {
        x |= i64(2) << 2 * k;
      } else if (~i & 1 && j & 1) {
        x |= i64(3) << 2 * k;
      }
    }
    return x;
  };
  auto f2 = [&](i64 x) -> array<int, 2> { // O(n)
    int i = 0, j = 0;
    for (int k = 0; k < n; k++, x >>= 2) {
      auto rem = x & 3;
      if (rem == 1 || rem == 2) {
        i |= 1 << k;
      }
      if (rem == 1 || rem == 3) {
        j |= 1 << k;
      }
    }
    return {i, j};
  };
  for (auto &&[type, x, y, d] : a) { // O(n*q)
    if (type == "->") {
      println(f1(x - 1, y - 1) + 1);
    } else {
      auto [i, j] = f2(d - 1);
      println(i + 1, j + 1);
    }
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
