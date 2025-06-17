/**
 * https://codeforces.com/contest/2121/submission/324944730
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

void solve(int t) {
  Int n;
  vector<Int> a(2 * n);
  vector<int> pos(2 * n + 1);
  vector<array<int, 2>> ans;
  for (int i = 0; i < 2 * n; i++) {
    pos[a[i]] = i;
  }
  auto move = [&](auto &p, int to) {
    swap(a[p], a[to]);
    swap(p, pos[a[p]]);
    assert(p == to);
  };
  for (int x = 1; x <= 2 * n; x++) {
    auto &p = pos[x];
    if (x % 2) {
      if (p >= n) {
        move(p, p - n); // move to first vector
        ans.push_back({3, p});
      }
      while (p > x / 2) {
        move(p, p - 1);
        ans.push_back({1, p});
      }
    } else {
      if (p < n) {
        move(p, p + n); // move to second vector
        ans.push_back({3, p - n});
      }
      while (p > x / 2 - 1 + n) {
        move(p, p - 1);
        ans.push_back({2, p - n});
      }
    }
  }
  println(ans.size());
  for (auto &&[type, i] : ans) {
    println(type, i + 1);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
