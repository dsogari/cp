/**
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

template <typename T> struct Str : basic_string<T> {
  using basic_string<T>::basic_string;
  Str() { cin >> *this; }
};
using String = Str<char>;

void solve(int t) {
  String s;
  int n = s.size();
  vector dp(n, vector<int>(n));
  vector top(n, vector<char>(n));
  for (int r = 1; r < n; r++) { // O(n^3)
    if (r < n - 1) {
      auto [mn, mx] = minmax(s[r - 1], s[r + 1]);
      dp[r][r] = mn > s[r] ? mx - s[r] : INT_MAX; // valley vs non-valley
    }
    for (int l = r - 1; l >= 0; l--) {
      auto &curC = dp[l][r] = INT_MAX;
      auto &curT = top[l][r] = max(s[l], s[r]);
      if (dp[l + 1][r - 1] < INT_MAX) {
        curC = dp[l + 1][r - 1] + abs(s[l] - s[r]);
        if ((r - l + 1) % 2) { // odd-length valley
          char mx = top[l + 1][r - 1] + 1;
          if (curT < mx && (s[l] > s[l + 1] || s[r - 1] < s[r])) { // conflict
            if (mx > 'z') {
              curC = INT_MAX; // cannot be resolved
            } else {
              curC += 2 * (mx - exchange(curT, mx));
            }
          }
        }
      }
      for (int m = r - 1; m > l; m--) {
        if (r - l > 3 && (m - l > 2 || (m - l == 1 && s[l] > s[m])) &&
            (r - m > 2 || (r - m == 1 && s[m] < s[r]))) {
          auto c0 = m - l > 2 ? dp[l + 1][m - 1] : 0;
          auto c1 = r - m > 2 ? dp[m + 1][r - 1] : 0;
          if (c0 < INT_MAX && c1 < INT_MAX) {
            auto c2 = c0 + c1;
            char tt = 0;
            if (m - l > 2) {
              auto t2 = max(s[l], s[m]);
              char mx = top[l + 1][m - 1] + 1;
              if (t2 < mx && (s[l] > s[l + 1] || s[m - 1] < s[m])) {
                if (mx > 'z') {
                  continue; // cannot be resolved
                } else {
                  c2 += 2 * (mx - t2);
                  tt = mx;
                }
              } else {
                tt = t2;
              }
            }
            if (r - m > 2) {
              auto t2 = max(s[m], s[r]);
              char mx = top[m + 1][r - 1] + 1;
              if (t2 < mx && (s[m] > s[m + 1] || s[r - 1] < s[r])) {
                if (mx > 'z') {
                  continue; // cannot be resolved
                } else {
                  c2 += 2 * (mx - t2 + abs(tt - mx));
                  tt = max(tt, mx);
                }
              } else {
                c2 += 2 * abs(tt - t2);
                tt = max(tt, t2);
              }
            }
            if (c2 < curC) {
              assert(tt > 0 && tt <= curT);
              curC = c2;
              curT = tt;
            }
          }
        }
        if (m + 1 < r) {
          auto c0 = dp[l][m];
          auto c1 = dp[m + 1][r];
          if (c0 < INT_MAX && c1 < INT_MAX) {
            auto c2 = c0 + c1;
            if (c2 < curC) {
              auto mx = max(top[l][m], top[m + 1][r]);
              assert(mx <= curT);
              curC = c2;
              curT = mx;
            }
          }
        }
      }
    }
  }
  int ans = dp[0][n - 1];
  if (ans == 0 || ans == INT_MAX) {
    ans = -1;
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
