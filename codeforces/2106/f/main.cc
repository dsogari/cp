/**
 * https://codeforces.com/contest/2106/submission/325496281
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
  i64 ans = 0, top = 0, bot = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && s[i - 1] == '1') {
      bot = 0;
    }
    if (s[i] == '0') {
      top += i;
      bot += n - i - 1;
    } else {
      bot++;
      top = bot;
    }
    ans = max({ans, top, bot});
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
