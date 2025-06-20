/**
 * https://codeforces.com/contest/2121/submission/325318454
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

void solve(int t) {
  Int n;
  Str s;
  vector<int> pref(n + 1);
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + (s[i] == '0' ? 1 : -1);
  }
  ranges::sort(pref); // we need the absolute value
  i64 ans = 0;
  for (int i = 0; i <= n; i++) {
    ans += i64(i + 1) * (n - i);       // sum of subarray lengths
    ans += i64(pref[i]) * (i + i - n); // sum of subarray sums
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
