/**
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

void solve(int t) {
  Int n, m, k;
  vector<array<Int, 2>> da(n);
  vector<int> milk(n + k - 1);
  for (auto &&[d, c] : da) { // O(n)
    milk[d] += c;
  }
  vector<int> fresh(k);
  int ans = 0;
  for (int i = 1, j = 0; i < n + k; i++, j = (j + 1) % k) { // O(n)
    fresh[j] += milk[i];
    if (fresh[j] >= m) {
      fresh[j] -= m;
      fresh[(j + 1) % k] += fresh[j];
      ans++;
    }
    fresh[j] = 0;
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
