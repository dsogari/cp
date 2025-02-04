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

void solve(int t) {
  Int n;
  vector<array<Int, 3>> a(n);
  vector<double> dist(n, INFINITY);
  vector<int> par(n, -1);
  set<pair<double, int>> q = {{0, 0}};
  dist[0] = 0;
  while (q.size()) { // O(n^2*log n)
    auto [du, u] = *q.begin();
    q.erase(q.begin());
    auto [xu, yu, hu] = a[u];
    for (int v = 0; v < n; v++) {
      auto &dv = dist[v];
      if (u != v && du < dv) {
        auto [xv, yv, hv] = a[v];
        i64 dx = xv - xu, dy = yv - yu;
        auto d = sqrt(dx * dx + dy * dy);
        if (d <= hu && du + d < dv) {
          q.erase({dv, v});
          dv = du + d;
          par[v] = u;
          q.insert({dv, v});
        }
      }
    }
  }
  if (par[n - 1] < 0) {
    println(0);
    return;
  }
  vector<int> ans;
  for (int u = n - 1; u != 0; u = par[u]) {
    ans.push_back(u + 1);
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
