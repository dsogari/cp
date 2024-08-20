/**
 * https://codeforces.com/contest/2001/submission/277512821
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

#ifdef ONLINE_JUDGE
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

#else
#include "tree.h"
int simulate(Graph &g, int a, int b) {
  Path path(g, a, b);
  return path[(path.size() - 1) / 2];
}
#endif

void solve(int t) {
  Int n;
#ifndef ONLINE_JUDGE
  Graph g(n, n - 1);
#endif
  int rem = 15 * n;
  auto query = [&](int a, int b) {
    assert(rem--);
    println('?', a, b);
#ifndef ONLINE_JUDGE
    return simulate(g, a, b);
#else
    return Int();
#endif
  };
  vector<int> ans;
  for (int a = 1, b; a < n; a++) { // O(n*log n)
    for (int x = n; x != a;) {
      b = x, x = query(a, b); // x is the middle node between a and b
    }
    ans.insert(ans.end(), {a, b});
  }
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
