/**
 * https://codeforces.com/contest/2121/submission/325217044
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

template <typename T> struct Str : basic_string<T> {
  using basic_string<T>::basic_string;
  Str() { cin >> *this; }
};
using String = Str<char>;

struct AsciiHist : array<int, CHAR_MAX + 1> {
  AsciiHist(const string &s) : array{} {
    for (auto &&c : s) {
      (*this)[c]++;
    }
  }
};

void solve(int t) {
  Int n;
  String s;
  AsciiHist cnt(s);
  for (int i = 1; i < n - 1; i++) {
    if (cnt[s[i]] > 1) {
      return println("YES");
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
