/**
 * https://codeforces.com/contest/2106/submission/325493864
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

struct DSU {
  vector<int> par;
  vector<i64> siz;
  DSU(int n) : par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(1)
  int merge(int a, int b) { // O(1) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += exchange(siz[b], 0);
      par[b] = a;
    }
    return a;
  }
  int count() const { return siz.size() - ranges::count(siz, 0); } // O(n)
};

void solve(int t) {
  Int n;
  Str s;
  DSU dsu(2 * n);
  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      dsu.siz[i] = i;
      dsu.siz[i + n] = n - i - 1;
    } else {
      dsu.siz[i + n] = 0;
    }
  }
  for (int i = 1; i < n; i++) {
    if (s[i] == '0') {
      if (s[i - 1] == '0') {
        dsu.merge(i, i - 1);
        dsu.merge(i + n, i + n - 1);
      } else {
        dsu.merge(i, i - 1);
      }
    } else if (s[i - 1] == '0') {
      dsu.merge(i, i + n - 1);
    }
  }
  i64 ans = 0;
  for (int i = 0; i < 2 * n; i++) {
    ans = max(ans, dsu.siz[dsu.find(i)]);
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
