/**
 * https://codeforces.com/contest/2005/submission/281279148
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

struct Str : string {
  Str() { cin >> *this; }
};

constexpr int lowerlatin = 'z' - 'a' + 1;
const string letters = "narek";

void solve(int t) {
  Int n, m;
  vector<Str> s(n);
  array<int, lowerlatin> valid;
  valid.fill(-1);
  array<int, 5> startc = {};
  for (int i = 0; i < 5; i++) {
    valid[letters[i] - 'a'] = startc[i] = i;
  }
  array<int, 5> dp0, dp1;
  dp0.fill(INT_MIN);
  dp0[0] = 0;
  for (int i = 0; i < n; i++) { // O(n*m*c)
    array<int, 5> start = startc, cnt = {};
    int total = 0;
    for (int j = 0; j < m; j++) {
      int c = valid[s[i][j] - 'a'];
      if (c >= 0) {
        for (int k = 0; k < 5; k++) {
          if (start[k] == c) {
            start[k] = (c + 1) % 5;
            cnt[k]++;
          }
        }
        total++;
      }
    }
    dp1 = dp0;
    for (int k = 0; k < 5; k++) {
      if (dp0[k] > INT_MIN) {
        auto &best = dp1[start[k]];
        best = max(best, dp0[k] + 2 * cnt[k] - total);
      }
    }
    swap(dp0, dp1);
  }
  int ans = 0;
  for (int k = 0; k < 5; k++) {
    if (dp0[k] > INT_MIN) {
      ans = max(ans, dp0[k] - 2 * k);
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
