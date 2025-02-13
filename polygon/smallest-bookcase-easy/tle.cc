/**
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

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  ranges::sort(a); // O(n*log n)
  vector<int> far(n);
  int ans = 1;
  for (int i = 0; i < n; i++) { // O(n^2)
    for (int j = i + 1; j < n; j++) {
      if (a[i][1] > a[j][1]) {
        far[j] = max(far[j], far[i] + 1);
        ans = max(ans, far[j] + 1);
      }
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
