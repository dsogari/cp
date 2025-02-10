/**
 * https://codeforces.com/contest/2065/submission/305387174
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Freq : vector<int> {
  Freq(const auto &a) : Freq(a, ranges::max(a)) {}
  Freq(const auto &a, int mx) : vector<int>(mx + 1) { // O(n)
    for (auto &&ai : a) {
      (*this)[ai]++;
    }
  }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  Freq cnt(a, n);
  vector<array<int, 2>> pairs(n + 1);
  for (int i = 2; i <= n; i++) { // O(n*log log n)
    if (!pairs[i][0]) {
      for (int j = i; j <= n; j += i) {
        int c = !!pairs[j][0] + !!pairs[j][1];
        for (int k = j; k % i == 0; k /= i, c++) {
          if (c == 2) {
            pairs[j] = {-1, -1};
            break;
          }
          pairs[j][c] = i;
        }
      }
    }
  }
  i64 ans = 0, primes = 0, squaredprimes = 0;
  for (int i = 2; i <= n; i++) { // O(n)
    if (!cnt[i]) {
      continue;
    }
    auto [p, q] = pairs[i];
    if (q == 0) { // prime
      primes += cnt[i];
      squaredprimes += i64(cnt[i]) * cnt[i];
    } else if (q > 0) { // semiprime
      ans += i64(cnt[i]) * (p == q ? cnt[p] : cnt[p] + cnt[q]);
      ans += i64(cnt[i]) * (cnt[i] + 1) / 2;
    }
  }
  ans += (primes * primes - squaredprimes) / 2;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
