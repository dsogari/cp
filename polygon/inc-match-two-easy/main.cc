/**
 * (c) 2024 Diego Sogari
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
  Int n;
  String s;
  if (n % 2 == 0) {
    return println("YES");
  }
  auto f = [&](int &l, int &r, int inc, int end) {
    while (l + inc != end && s[l + inc] >= s[l] && s[l] <= s[r]) {
      l += inc;
    }
    return abs(r - l + 1) % 2;
  };
  for (int i = 1; i < n; i++) { // O(n)
    if (s[i - 1] > s[i] && s[i] < s[i + 1]) {
      for (int l = i, r = i; true;) {
        if (f(l, r, -1, -1) || f(r, l, 1, n)) {
          return println("YES");
        }
        if (s[l] < s[r] ? l == 0 || s[l - 1] < s[l]
                        : r == n - 1 || s[r + 1] < s[r]) {
          i = r;
          break;
        }
      }
    }
  }
  println("NO");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
