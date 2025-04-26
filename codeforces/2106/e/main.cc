/**
 * https://codeforces.com/contest/2106/submission/317333494
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
  vector<int> pp(n + 1);
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    pp[p[i]] = i + 1;
  }
  for (auto &&[l, r, k] : b) {
    if (pp[k] < l || pp[k] > r) {
      ans.push_back(-1);
      continue;
    }
    int lt = 0, gt = 0, left = 0, right = 0;
    while (l <= r && lt < k && n + 1 - gt > k) {
      auto m = (l + r) / 2;
      if (pp[k] == m) {
        break;
      }
      if (pp[k] < m) {
        left += p[m - 1] < k;
        gt++;
        r = m - 1;
      } else {
        right += p[m - 1] > k;
        lt++;
        l = m + 1;
      }
    }
    if (lt >= k || n + 1 - gt <= k) {
      ans.push_back(-1);
      continue;
    }
    ans.push_back(2 * max(left, right));
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
