/**
 * https://codeforces.com/contest/1986/submission/283938075
 *
 * (c) 2024 Diego Sogari
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Divisors : vector<vector<int>> {
  Divisors(int n) : vector<vector<int>>(n + 1) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

void solve(int t) {
  Int n;
  vector<Int> a(1, 0);
  a.resize(n + 1);
  vector<vector<int>> num(n + 1), den(n + 1);
  int amx = 0, bmx = 0;
  for (int i = 1; i <= n; i++) {
    auto g = gcd(+a[i], i);
    auto x = a[i] / g, y = i / g;
    num[x].push_back(y);
    den[y].push_back(x);
    amx = max(amx, x);
    bmx = max(bmx, y);
  }
  Divisors divisors(amx);
  vector<int> c(bmx + 1);
  i64 ans = -den[1].size();
  for (int bi = 1; bi <= n; bi++) {
    if (den[bi].size()) {
      for (int aj = bi; aj <= amx; aj += bi) {
        for (auto &bj : num[aj]) {
          c[bj]++;
        }
      }
      for (auto &ai : den[bi]) {
        for (auto &bj : divisors[ai]) {
          if (bj <= bmx) {
            ans += c[bj];
          }
        }
      }
      for (int aj = bi; aj <= amx; aj += bi) {
        for (auto &bj : num[aj]) {
          c[bj] = 0;
        }
      }
    }
  }
  println(ans / 2);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
