/**
 * https://codeforces.com/contest/2060/submission/302299315
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n;
  vector<Int> a(n), b(n);
  vector<int> pos(2 * n + 1);
  int flips = 0, extra = n % 2;
  for (int i = 0; i < n; i++) { // O(n)
    if (a[i] > b[i]) {
      swap(a[i], b[i]);
      flips++;
    }
    pos[a[i]] = pos[b[i]] = i;
  }
  for (int i = 0, x = 0, prev = 0; i < n; i++) { // O(n)
    while (pos[++x] < 0)
      ;
    auto y = b[pos[x]];
    if (prev > y) {
      println("NO");
      return;
    }
    pos[x] = pos[y] = -1; // mark as visited
    extra |= prev < x && i % 2;
    prev = y;
  }
  auto ans = flips % 2 == 0 || extra ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
