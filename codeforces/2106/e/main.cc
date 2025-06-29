/**
 * https://codeforces.com/contest/2106/submission/317336778
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
  Int n, q;
  vector<Int> p(n);
  vector<array<Int, 3>> b(q);
  vector<int> pp(n + 1), ans;
  for (int i = 0; i < n; i++) {
    pp[p[i]] = i + 1;
  }
  for (auto &&[l, r, k] : b) {
    if (pp[k] < l || pp[k] > r) {
      ans.push_back(-1);
      continue;
    }
    int c = -1;
    for (int lt = 0, gt = 0, x = 0, y = 0; lt < k && n + 1 - gt > k;) {
      auto m = (l + r) / 2;
      if (pp[k] == m) {
        c = 2 * max(x, y);
        break;
      }
      if (pp[k] < m) {
        x += p[m - 1] < k;
        gt++;
        r = m - 1;
      } else {
        y += p[m - 1] > k;
        lt++;
        l = m + 1;
      }
    }
    ans.push_back(c);
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
