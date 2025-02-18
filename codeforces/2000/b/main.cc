/**
 * https://codeforces.com/contest/2000/submission/276304146
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

void solve(int t) {
  Int n;
  vector<Int> a(n);
  vector<bool> seat(n + 1);
  bool first = false;
  for (auto &ai : a) {
    if (first) {
      auto prev = ai > 1 && seat[ai - 1];
      auto next = ai < n && seat[ai + 1];
      if (!prev && !next) {
        println("NO");
        return;
      }
    }
    seat[ai] = first = true;
  }
  println("YES");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
