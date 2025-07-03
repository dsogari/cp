/**
 * https://codeforces.com/contest/2114/submission/327195973
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

struct Sieve : vector<int> {
  Sieve(int n, bool isval) { // max value or min count
    int mx = isval ? n : ceil(n * log(n * log(n + 1) + 1) + 1);
    vector<bool> vis(mx + 1);
    for (int i = 2; i <= mx; i++) { // O(mx*log log mx)
      if (!vis[i]) {
        push_back(i);
        for (int j = 2 * i; j <= mx; j += i) {
          vis[j] = true;
        }
      }
    }
  }
} sieve(1e6, true);

struct PrimeFactors : vector<int> {
  PrimeFactors(const auto &primes, int n) { // O(log log n)
    for (auto &&p : primes) {
      if (p > n) {
        break;
      } else if (n % p == 0) {
        push_back(p);
      }
    }
  }
};

map<array<int, 3>, int> memo;

void solve(int t) {
  Int x, y, k;
  auto f = [&](int x) { // O(n)
    if (x == 1) {
      return 0;
    }
    if (x <= k) {
      return 1;
    }
    map<int, int> dp;
    for (int i = 2; i <= k && i * i <= x; i++) { // O(sqrt n)
      if (x % i == 0) {
        dp.emplace(i, 1);
        if (x / i <= k) {
          dp.emplace(x / i, 1);
        }
      }
    }
    for (auto &&[d1, c1] : dp) { // O(n)
      for (auto &&[d2, c2] : dp) {
        if (d2 >= d1 && d2 < x) {
          auto y = d1 * d2;
          if (y > k && x % y == 0) {
            auto &c = dp[y];
            c = min(c ? c : INT_MAX, c1 + c2);
          }
        }
      }
    }
    return dp.contains(x) ? dp[x] : -1;
  };
  auto g = gcd(+x, +y);
  auto a = f(x / g);
  auto b = f(y / g);
  if (a < 0 || b < 0) {
    return println(-1);
  }
  auto ans = a + b;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
