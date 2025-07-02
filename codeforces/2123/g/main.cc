/**
 * https://codeforces.com/contest/2123/submission/327120337
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

using Int = Number<int>;

struct Query {
  Int type, k, x = type == 1 ? Int() : Int(0);
};

constexpr auto absmod(auto x, auto m) { return (m + x % m) % m; };

void solve(int t) {
  Int n, m, q;
  vector<Int> a(n);
  vector<Query> b(q);
  map<int, i64> memo;
  for (auto &&[type, k, x] : b) {
    if (type == 2) {
      memo.emplace(gcd(+m, +k), 0);
    }
  }
  for (auto &&[g, sum] : memo) {
    for (int i = 0, prev = 0; i < n; prev = a[i++]) {
      sum += absmod(a[i] - prev, g);
    }
  }
  auto f = [&](int i, int x) {
    auto prev = i == 0 ? 0 : +a[i - 1];
    for (auto &&[g, sum] : memo) {
      sum += absmod(x - prev, g) - absmod(a[i] - prev, g);
      if (i < n - 1) {
        sum += absmod(a[i + 1] - x, g) - absmod(a[i + 1] - a[i], g);
      }
    }
    a[i] = x;
  };
  for (auto &&[type, k, x] : b) {
    if (type == 1) {
      f(k - 1, x);
    } else {
      auto ans = memo[gcd(+m, +k)] < m ? "YES" : "NO";
      println(ans);
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
