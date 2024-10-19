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

void solve(int t) {
  Int n;
  vector<Int> a(n);
  vector<int> b(2 * n + 1);
  for (auto &&ai : a) {
    b[ai]++;
  }
  int ans = 0;
  for (int i = 0, j = 0, len = 1; j < b.size();) {
    for (; !b[i]; i++)
      ;
    for (; j < b.size() && !b[j]; j++)
      ;
    if (j == b.size()) {
      break;
    }
    auto diff = j - i;
    if (diff > len) {
      len--;
      i++;
    } else {
      if (diff > 1) {
        ans = max(ans, diff);
      }
      len++;
      j++;
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
