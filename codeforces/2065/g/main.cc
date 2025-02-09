/**
 * https://codeforces.com/contest/2065/submission/305377723
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

struct BigOmega : vector<int> {
  BigOmega(int n) : vector<int>(n + 1) { // O(n*log log n)
    for (int i = 2; i <= n; i++) {
      if (!(*this)[i]) {
        for (int j = i; j <= n; j += i) {
          for (int k = j; k % i == 0; k /= i) {
            (*this)[j]++;
          }
        }
      }
    }
  }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);              // O(n)
  Freq cnt(a, n);                // O(n)
  BigOmega omega(n);             // O(n*log log n)
  vector<int> pref(n + 1);       // O(n)
  for (int i = 2; i <= n; i++) { // O(n)
    pref[i] += pref[i - 1] + (omega[i] == 1 ? cnt[i] : 0);
  }
  i64 ans = 0;
  for (int i = 2; i <= n; i++) { // O(n*log n)
    if (omega[i] < 3 && cnt[i]) {
      if (omega[i] == 1) {
        ans += i64(cnt[i]) * (pref[n] - pref[i]); // prime vs prime
      }
      if (omega[i] == 2) {
        ans += i64(cnt[i]) * (cnt[i] + 1) / 2;
      }
      for (int j = i + i; j <= n; j += i) {
        if (omega[j] == 2) {
          ans += i64(cnt[i]) * cnt[j];
        }
      }
    }
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
