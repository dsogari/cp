/**
 * https://codeforces.com/contest/2114/submission/326807590
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
  set<array<int, 3>> vis;
  auto dfs = [&](auto &dfs, auto &factors, int x, int y, int z, int c,
                 int &best) -> void {
    if (y == x) {
      best = min(best, c);
      return;
    }
    if (!vis.insert({y, z, c}).second) {
      return;
    }
    for (auto p : factors) {
      auto yy = y * p;
      if (yy > x) {
        break;
      } else if (z * p > k) {
        dfs(dfs, factors, x, yy, p, c + 1, best);
      } else {
        dfs(dfs, factors, x, yy, z * p, c, best);
      }
    }
  };
  auto f = [&](int x) {
    auto [it, ok] = memo.insert({{x, k}, INT_MAX});
    auto &ans = it->second;
    if (ok) {
      PrimeFactors factors(sieve, x); // O(log x)
      if (factors.empty()) {
        ans = 0;
      } else if (factors.back() > k) {
        ans = -1;
      } else {
        vis.clear();
        dfs(dfs, factors, x, 1, 1, 1, ans); // O((log x)!)
      }
    }
    return ans;
  };
  auto g = gcd(+x, +y);
  auto c1 = f(x / g);
  if (c1 < 0) {
    return println(-1);
  }
  auto c2 = f(y / g);
  if (c2 < 0) {
    return println(-1);
  }
  auto ans = c1 + c2;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
