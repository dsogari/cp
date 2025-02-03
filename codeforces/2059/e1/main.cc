/**
 * https://codeforces.com/contest/2059/submission/304278109
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, m;
  vector<Int> a(n * m), b(n * m);
  int i = 0;
  for (int j = 0; j < n * m;) {
    if (a[i] == b[j]) {
      if (i % m == 0 && j - i < m) {
        auto saved = i;
        for (int k = j % m; k < m; k++, i++, j++) {
          if (a[i] != b[j]) {
            i = saved;
            goto end;
          }
        }
      } else {
        i++, j++;
      }
    } else {
      j++;
    }
  }
end:
  int ans = n * m - i;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
