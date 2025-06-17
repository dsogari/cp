/**
 * https://codeforces.com/contest/2121/submission/324958476
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
  auto diff = to_string(stoi(r) - stoi(l));
  diff = string(l.size() - diff.size(), '0') + diff;
  int ans = 0;
  for (int i = 0; i < l.size(); i++) {
    auto d = r[i] - l[i] + (l[i] <= r[i] ? 0 : 10);
    if (diff[i] > '0') {
      ans += d == 1;
      break;
    }
    ans += 2 - min(2, d);
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
