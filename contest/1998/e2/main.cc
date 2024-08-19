/**
 * https://codeforces.com/contest/1998/submission/277254064
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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
    nodes.emplace_back(-1, -1, -1, -1, -1);
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
    }
    if (top < 0 || f(top, i)) {
      top = i;
    }
    nodes[i].start = nodes[i].par + 1;
    above.push(i);
  }
  void finish() { // O(n)
    while (!above.empty()) {
      nodes[above.top()].end = nodes.size();
      above.pop();
    }
  }
};

void solve(int t) { // O(n^2)
  Int n, x;
  vector<Int> a(n);
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  Treap treap(cmp);
  vector<i64> sum(n + 1);
  vector<int> cnt(n + 1);
  auto f = [&](auto &self, int u, int end) { // O(n)
    if (u < 0) {
      return;
    }
    auto [p, l, r, s, e] = treap.nodes[u];
    auto st = sum[e < 0 ? end : e] - sum[s]; // sum of subtree
    cnt[u + 1] = p < 0 || st >= a[p] ? cnt[l + 1] + cnt[r + 1] + 1 : 0;
    self(self, p, end);
  };
  vector<int> ans(n);
  for (int i = 0; i < n; i++) { // O(n^2)
    sum[i + 1] += sum[i] + a[i];
    treap.push(i);
    auto l = treap.nodes[i].left;
    f(f, l >= 0 ? l : i, i + 1);
    ans[i] = cnt[treap.top + 1];
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
