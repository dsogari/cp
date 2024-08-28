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

int invcount(auto &&f, int s, int e) { // [s, e) O(n^2)
  int ans = 0;
  for (int i = s; i < e; i++) {
    for (int j = i + 1; j < e; j++) {
      ans += f(j, i);
    }
  }
  return ans;
}

void solve(int t) { // O(n^2+m)
  Int n, m;
  vector<array<Int, 2>> intervals(m);
  vector<int> a(n), left;
  int lastl = 0, lastr = 0, prevr = 0, x = n;
  for (int i = 0; i < m; i++) { // O(m)
    auto [l, r] = intervals[i];
    a[l - 1] = -1;
    lastl = max<int>(lastl, l);
    if (r > lastr) {
      prevr = lastr;
      lastr = r;
    }
  }
  for (int i = 0; i < lastl - 1; i++) { // O(n)
    if (a[i] == 0) {
      a[i] = x--;
    } else {
      left.push_back(i);
    }
  }
  if (m > 1) {
    assert(left.size() == m - 1);
    a[lastr - 1] = x--;
  } else {
    for (int i = lastl; i < lastr; i++) { // O(n)
      if (a[i] == 0) {
        a[i] = x--;
      }
    }
  }
  for (int i = 0; i < n; i++) { // O(n)
    if (a[i] <= 0) {
      a[i] = x--;
    }
  }
  if (m > 1) {
    while (true) {
      int j = lastr - 1;
      auto y = a[j--];
      while (a[j] < y && j >= prevr) {
        j--;
      }
      if (j >= prevr) {
        auto inv1 = y - (n - lastr) - 1, inv2 = lastr - 1 - j;
        if (inv1 > inv2) {
          a[lastr - 1] = a[j];
          a[j] = a[left[m - 2]];
          for (int i = m - 2; i > 0; i--) {
            a[left[i]] = a[left[i - 1]];
          }
          a[left[0]] = y;
        }
      }
      if (j <= prevr) {
        break;
      }
    }
  }
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  int ans = invcount(cmp, 0, n); // O(n^2)
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
