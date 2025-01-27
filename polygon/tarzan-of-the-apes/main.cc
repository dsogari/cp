/**
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n;
  vector<array<Int, 3>> a(n);
  auto cmp = [&](int i, int j) { return a[i][0] < a[j][0]; };
  Iota idx(n, cmp); // O(n*log n)
  vector<double> dist(n, INFINITY);
  vector<int> par(n, -1);
  vector<bool> vis(n);
  auto f = [&](int u, int v) { // O(1)
    if (dist[u] < dist[v]) {
      auto [xu, yu, hu] = a[idx[u]];
      auto [xv, yv, hv] = a[idx[v]];
      auto dx = xv - xu, dy = yv - yu;
      if (abs(dx) > hu) {
        return false;
      }
      auto d = sqrt(i64(dx) * dx + i64(dy) * dy);
      if (d <= hu && dist[u] + d < dist[v]) {
        dist[v] = dist[u] + d;
        par[v] = u;
      }
    }
    return true;
  };
  auto first = ranges::find(idx, 0) - idx.begin();
  auto last = ranges::find(idx, n - 1) - idx.begin();
  dist[first] = 0;
  for (int i = 0; i < n; i++) { // O(n^2)
    int u = -1;
    for (int v = 0; v < n; v++) {
      if (!vis[v] && (u == -1 || dist[v] < dist[u])) {
        u = v;
      }
    }
    if (isinf(dist[u])) {
      break;
    }
    vis[u] = true;
    for (int v = u - 1; v >= 0 && f(u, v); v--)
      ; // search left
    for (int j = u + 1; j < n && f(u, j); j++)
      ; // search right
  }
  if (par[last] < 0) {
    println(0);
    return;
  }
  vector<int> ans;
  for (int u = last; u != first; u = par[u]) {
    ans.push_back(idx[u] + 1);
  }
  ranges::reverse(ans);
  println(ans.size());
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
