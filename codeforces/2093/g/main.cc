/**
 * https://codeforces.com/contest/2093/submission/327840622
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

using Int = Number<int>;

template <typename T, size_t N> struct Trie {
  vector<pair<T, array<int, N>>> nodes;
  Trie(int cap = 1) : nodes(1) { nodes.reserve(cap); }
  void visit(auto &&f, auto &&x, auto &&...args) {
    for (int i = 0, j = 0;; j++) {
      int k = f(nodes[i], j, x, args...);
      if (k < 0) {
        break;
      }
      assert(k < N);
      auto &child = nodes[i].second[k];
      if (!child) {
        child = nodes.size();
        nodes.emplace_back(); // might invalidate references
      }
      i = nodes[i].second[k];
    }
  }
};

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  Trie<int, 2> trie(n);
  int len = bit_width<unsigned>(*ranges::max_element(a)); // O(n)
  if (len < bit_width<unsigned>(k)) {
    return println(-1);
  }
  int ans = INT_MAX;
  auto add = [&](auto &node, int j, unsigned x, int i) -> int {
    node.first = i;
    return j < len ? (x >> len - 1 - j) & 1 : -1;
  };
  auto get = [&](auto &node, int j, unsigned x, int i) -> int {
    if (j == len) {
      ans = min(ans, i - node.first + 1);
      return -1; // x ^ y == k
    }
    auto bitx = (x >> len - 1 - j) & 1;
    auto bitk = (k >> len - 1 - j) & 1;
    auto xorc = node.second[!bitx]; // x ^ y > k
    if (!bitk && xorc) {
      auto &child = trie.nodes[xorc];
      ans = min(ans, i - child.first + 1);
    }
    return !bitk ? bitx : xorc ? !bitx : -1;
  };
  for (int i = 0; i < n; i++) { // O(n*log A)
    trie.visit(add, a[i], i);
    trie.visit(get, a[i], i);
  }
  if (ans == INT_MAX) {
    ans = -1;
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
