/**
 * https://codeforces.com/contest/2121/submission/325214453
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

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

void solve(int t) {
  Str l, r;
  int ans = 0, i = 0;
  for (; i < l.size() && l[i] == r[i]; i++) {
    ans += 2;
  }
  if (i < l.size() && r[i] - l[i] == 1) {
    ans++;
    for (i++; i < l.size() && r[i] - l[i] == -9; i++) {
      ans++;
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
