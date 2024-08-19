/**
 * https://codeforces.com/contest/1998/submission/277248438
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

void solve(int t) { // O(n)
  Int n, x;
  vector<Int> a(n);
  auto cmp = [&](int i, int j) { return a[i] < a[j]; };
  Treap treap(cmp);
  for (int i = 0; i < n; i++) { // O(n)
    treap.push(i);
  }
  auto f = [&](auto &self, int u) -> pair<i64, int> { // O(n)
    if (u < 0) {
      return {0, 0};
    }
    auto [_p, l, r, _s, _e] = treap.nodes[u];
    auto [sl, cl] = self(self, l);
    auto [sr, cr] = self(self, r);
    cl = sl >= a[u] ? cl + 1 : 0; // reset if left child cannot merge
    cr = sr >= a[u] ? cr + 1 : 0; // reset if right child cannot merge
    return {a[u] + sl + sr, cl + cr};
  };
  auto [_, ans] = f(f, treap.top);
  println(ans + 1); // the top node can always remain
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
