/**
 * https://codeforces.com/contest/2000/submission/276310357
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

struct Str : string {
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  Str s;
  vector<i64> sum(n + 1);
  for (int i = 0; i < n; i++) {
    sum[i + 1] += sum[i] + a[i];
  }
  i64 ans = 0;
  for (int i = 0, j = n - 1; i < j;) {
    if (s[i] == 'L' && s[j] == 'R') {
      ans += sum[j + 1] - sum[i];
      i++, j--;
    } else {
      i += s[i] == 'R';
      j -= s[j] == 'L';
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
