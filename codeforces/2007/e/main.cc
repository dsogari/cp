/**
 * https://codeforces.com/contest/2007/submission/280273967
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
using I64 = Num<i64>;

void solve(int t) { // O(n)
  Int n;
  I64 w;
  vector<Int> p(n - 1);
  vector<array<I64, 2>> ev(n - 1);
  vector<int> size(n + 1), len(n + 1, 1);
  for (int u = n; u > 1; u--) { // O(n)
    size[p[u - 2]] += size[u] + 1;
    len[u + size[u]] += u < n;
  }
  vector<i64> ans;
  int cnt = n;
  i64 sum = 0;
  for (auto &&[x, y] : ev) { // O(n)
    auto u = (x + n - 2) % n + 1, v = x + size[x];
    cnt -= !--len[u] + !--len[v];
    sum += y;
    ans.push_back((w - sum) * cnt + sum * 2);
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
