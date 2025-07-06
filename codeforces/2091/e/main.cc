/**
 * https://codeforces.com/contest/2091/submission/327836833
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

struct Omega : vector<int> {
  Omega(int n) : vector<int>(n + 1) { // O(n*log log n)
    for (int i = 2; i <= n; i++) {
      if (!(*this)[i]) {
        for (int j = i; j <= n; j += i) {
          (*this)[j]++;
        }
      }
    }
  }
};

void solve(int t) {
  Int n;
  Omega omega(n);                                      // O(n*log log n)
  int ans = accumulate(omega.begin(), omega.end(), 0); // O(n)
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
