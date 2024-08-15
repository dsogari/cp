/**
 * https://codeforces.com/contest/1993/submission/276851167
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

struct Str : string {
  Str() { cin >> *this; }
};

constexpr int absmod(int x, int m) { return (m + x % m) % m; };

void solve(int t) {
  Int n, k, w, h;
  Str s;
  unordered_map<int, vector<int>> hori, vert;
  int x = 0, y = 0;
  for (int i = 0; i < n; i++) { // O(n)
    x += (s[i] == 'L') - (s[i] == 'R');
    y += (s[i] == 'U') - (s[i] == 'D');
    hori[absmod(x, 2 * w)].push_back(i);
    vert[absmod(y, 2 * h)].push_back(i);
  }
  vector<bool> vis(n);
  int ans = 0;
  auto f = [&](int x, auto &a, bool val, bool count) { // O(n)
    for (auto i : a[x]) {
      ans += count && vis[i];
      vis[i] = val;
    }
  };
  for (int i = 0, x0 = 0, y0 = 0; i < k; i++, x0 -= x, y0 -= y) { // O(n*k)
    f(absmod(x0, 2 * w), hori, true, false);
    f(absmod(y0, 2 * h), vert, false, true);
    f(absmod(x0, 2 * w), hori, false, false);
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
