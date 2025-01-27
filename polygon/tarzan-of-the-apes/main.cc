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
  vector<int> par(n, -1);
  vector<double> dist(n, INFINITY);
  queue<int> q;
  auto first = ranges::find(idx, 0) - idx.begin();
  auto last = ranges::find(idx, n - 1) - idx.begin();
  q.push(first);
  dist[first] = 0;
  auto f = [&](int i, int j) { // O(1)
    if (dist[i] >= dist[j]) {
      return true;
    }
    auto [xi, yi, hi] = a[idx[i]];
    auto [xj, yj, hj] = a[idx[j]];
    auto dx = xj - xi, dy = yj - yi;
    if (abs(dx) > hi) {
      return false;
    }
    auto d = sqrt(i64(dx) * dx + i64(dy) * dy);
    if (d <= hi) {
      if (isinf(dist[j]) && d + hj > hi) {
        q.push(j);
      }
      if (dist[i] + d < dist[j]) {
        dist[j] = dist[i] + d;
        par[j] = i;
      }
    }
    return true;
  };
  while (q.size()) { // O(n^2)
    auto i = q.front();
    q.pop();
    for (int j = i + 1; j < n && f(i, j); j++)
      ; // search right
    for (int j = i - 1; j >= 0 && f(i, j); j--)
      ; // search left
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
