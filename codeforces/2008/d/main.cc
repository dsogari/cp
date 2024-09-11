/**
 * https://codeforces.com/contest/2008/submission/280681934
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
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
  Str() { cin >> *this; }
};

struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n, -1), siz(n) {}
  bool has(int v) const { return par[v] != -1; }                      // O(1)
  int add(int v) { return siz[v] = 1, par[v] = v; }                   // O(1)
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
  Int n;
  vector<Int> p(n);
  Str s;
  DSU dsu(n);
  map<int, int> cnt;
  for (int i = 0; i < n; i++) {
    dsu.add(i);
  }
  for (int i = 0; i < n; i++) {
    auto a = dsu.find(i);
    auto b = dsu.find(p[i] - 1);
    auto prev = cnt[a] + (a != b ? cnt[b] : 0);
    auto id = dsu.merge(i, p[i] - 1);
    cnt[id] = prev + (s[i] == '0');
  }
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = cnt[dsu.find(i)];
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
