/**
 * Bookcase
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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
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

struct Digraph : vector<vector<int>> {
  const int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

int binsearch(auto &&f, int s, int e) { // [s, e) O(log n)
  for (int inc = s < e ? 1 : -1; s != e;) {
    auto m = midpoint(s, e);
    f(m) ? s = m + inc : e = m;
  }
  return s; // first such that f is false
}

array<vector<int>, 2> lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> inc, len;
  for (int i = s; i < e; i++) {
    if (inc.empty() || f(inc.back(), i)) {
      inc.push_back(i);
      len.push_back(1);
    } else {
      auto j = ranges::lower_bound(inc, i, f) - inc.begin();
      inc[j] = i;
      len[j]++;
    }
  }
  return {inc, len};
}

int len1(auto &&b, int n, int k) { // O(k^n)
  vector<int> s(k, -1), c(k);
  int ans = n;
  auto f = [&](auto &self, int i) -> void {
    if (i == n) {
      ans = min(ans, *ranges::max_element(c));
      return;
    }
    for (int j = 0; j < k; j++) {
      if (s[j] < 0 || b[s[j]][1] <= b[i][1]) {
        auto saved = s[j];
        s[j] = i, c[j]++;
        self(self, i + 1);
        s[j] = saved, c[j]--; // backtrack
      }
    }
  };
  f(f, 0);
  return ans;
}

int len2(auto &&b, int n, int k, int mxlen) { // O(n^2 + ?)
  Digraph g(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (b[i][1] <= b[j][1]) {
        g.add(i, j);
      }
    }
  }
  vector<bool> vis(n);
  auto f = [&](int len) {
    auto dfs = [&](auto &self, int u, int i, int j) -> bool {
      vis[u] = true;
      if (j < len) {
        for (auto &&v : g[u]) {
          if (!vis[v] && self(self, v, i, j + 1)) {
            vis[u] = false;
            return true;
          }
        }
      }
      bool ans = true;
      auto v = ranges::find(vis, false) - vis.begin();
      if (v < n) {
        ans = i < k && self(self, v, i + 1, 1);
      } else {
        assert(i == k);
      }
      vis[u] = false;
      return ans;
    };
    return !dfs(dfs, 0, 1, 1);
  };
  assert(k > 0 && k <= n);
  return binsearch(f, n / k, mxlen + 1);
}

int len3(auto &&b, int n, int k, int mxlen) { // O(n^2 + ?)
  Digraph g(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (b[i][1] > b[j][1]) {
        g.add(i, j);
      }
    }
  }
  return 0;
}

auto now() { return chrono::high_resolution_clock::now(); }

void solve(int t) {
  // Int n;
  // vector<array<Int, 2>> b(n);
  int n = 12;
  vector<array<int, 2>> b(n);
  for (auto &&bi : b) {
    bi[0] = rand() % n + 1;
    bi[1] = rand() % n + 1;
  }
  ranges::sort(b); // O(n*log n)
  auto cmp = [&](int i, int j) { return b[i][1] > b[j][1]; };
  auto [seq, cnt] = lis(cmp, 0, n); // O(n*log n)
  int k = seq.size(), mxlen = *ranges::max_element(cnt);
  auto t0 = now();
  int l1 = len1(b, n, k);
  auto t1 = now();
  int l2 = len2(b, n, k, mxlen);
  auto t2 = now();
  int l3 = len3(b, n, k, mxlen);
  auto t3 = now();
  assert(l1 == l2);
  // assert(l1 == l3);
  println(b, k, l1, l2, l3);
  // chrono::duration<double, milli> d1 = t1 - t0, d2 = t2 - t1;
  // println("OK", d1.count(), "ms", d2.count(), "ms");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  // srand(time(0));
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
