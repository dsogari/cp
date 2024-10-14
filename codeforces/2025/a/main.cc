/**
 * https://codeforces.com/contest/2025/submission/285848238
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
  int mx = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == b[i]) {
      mx++;
    } else {
      break;
    }
  }
  mx += a.size() + b.size() - 2 * mx + (mx > 0);
  println(mx);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
