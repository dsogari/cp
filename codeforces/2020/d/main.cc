/**
 * https://codeforces.com/contest/2020/submission/283682972
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

struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(1)
  int merge(int a, int b) { // O(1) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += siz[b];
      par[b] = a;
    }
    return a;
  }
};

void solve(int t) {
  Int n, m;
  vector<array<Int, 3>> ops(m);
  vector by_d(11, vector<set<array<int, 2>>>(11));
  for (auto &&[a, d, k] : ops) { // O(m*log m)
    if (k > 0) {
      assert(d >= 1 && d <= 10);
      a--;
      by_d[d][a % d].insert({a, a + d * k});
    }
  }
  DSU dsu(n);
  for (int i = 1; i <= 10; i++) { // O(d^2*n)
    for (int j = 0; j < i; j++) {
      int last = 0;
      for (auto [l, r] : by_d[i][j]) {
        for (last = max(last, l); last + i <= r; last += i) {
          dsu.merge(last, last + i);
        }
      }
    }
  }
  set<int> components;
  for (int i = 0; i < n; i++) {
    components.insert(dsu.find(i));
  }
  int ans = components.size();
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
