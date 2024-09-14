/**
 * https://codeforces.com/contest/2005/submission/281192328
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

const string vowels = "aeiou";

void solve(int t) {
  Int n;
  string ans;
  auto m = n / 5, extra = n % 5;
  for (int i = 0; i < 5; i++, extra--) {
    ans += string(m + (extra > 0), vowels[i]);
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
