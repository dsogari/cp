/**
 * https://codeforces.com/contest/1998/submission/277320415
 *
 * Inspired by neal's solution:
 * https://codeforces.com/contest/1998/submission/275679381
 *
 * (c) 2024 Diego Sogari
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

struct Treap {
  struct Info {
    int par, left, right, start, end; // [start,end) of subtree
  };
  vector<Info> nodes;
  stack<int> above; // minimum stack
  function<bool(int, int)> f;
  int top = -1;
  Treap(auto &&f) : f(f) {}
  void push(int i) { // O(1) amortized / i must be pushed in order
    assert(i == nodes.size());
    nodes.emplace_back(-1, -1, -1, i, -1);
    int last = -1;
    while (above.size() && f(above.top(), i)) {
      last = above.top();
      nodes[last].end = i;
      above.pop();
    }
    if (above.size()) {
      nodes[i].par = above.top(); // smallest greater or equal
      nodes[above.top()].right = i;
    }
    if (last >= 0) {
      nodes[last].par = i;
      nodes[i].left = last; // greatest smaller
      nodes[i].start = nodes[last].start;
    }
    if (top < 0 || f(top, i)) {
      top = i;
    }
    above.push(i);
  }
  void finish() { // O(n)
    while (!above.empty()) {
      nodes[above.top()].end = nodes.size();
      above.pop();
    }
  }
};

void solve(int t) { // O(n)
  Int n, x;
  vector<Int> a(n);
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  Treap treap(cmp);
  vector<i64> sum(n + 1);
  for (int i = 0; i < n; i++) { // O(n)
    treap.push(i);
    sum[i + 1] += sum[i] + a[i];
  }
  treap.finish();
  vector<int> far(n);
  for (int i = 0, j = 0; i < n; i++) { // O(n)
    for (; j < n && sum[j + 1] - sum[i + 1] < a[i]; j++)
      ;
    far[i] = j;
  }
  vector<array<int, 2>> ranges(n);
  auto f = [&](auto &self, int u, int L, int R) { // O(n)
    if (u < 0) {
      return;
    }
    ranges[u] = {L, R};
    auto [_p, l, r, s, e] = treap.nodes[u];
    auto sl = sum[u] - sum[s];
    auto sr = sum[e] - sum[u + 1];
    self(self, l, L, sl >= a[u] ? R : u);
    self(self, r, sr >= a[u] ? L : u + 1, R);
  };
  f(f, treap.top, 0, n);
  vector<int> inc(n + 1);
  for (int i = 0; i < n; i++) { // O(n)
    auto [l, r] = ranges[i];
    if (l == 0 && far[i] < r) {
      inc[far[i]]++;
      inc[r]--;
    }
  }
  vector<int> ans(n);
  for (int i = 0, c = 1; i < n; i++) { // O(n)
    c += inc[i];
    ans[i] = c;
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
