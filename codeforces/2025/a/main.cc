/**
 * https://codeforces.com/contest/2025/submission/285939589
 *
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

struct Str : string {
  using string::string;
  Str() { cin >> *this; }
};

void solve(int t) {
  Str a, b;
  int i = 0;
  while (i < a.size() && a[i] == b[i]) { // O(|a|) a/b has null-terminator
    i++;
  }
  int ans = a.size() + b.size() - i + (i > 0);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
