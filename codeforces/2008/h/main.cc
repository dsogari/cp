/**
 * https://codeforces.com/contest/2008/submission/283959824
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

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

int binsearch(auto &&f, int s, int e) { // [s, e) O(log n)
  for (int inc = s < e ? 1 : -1; s != e;) {
    auto m = midpoint(s, e);
    f(m) ? s = m + inc : e = m;
  }
  return s; // first such that f is false
}

void solve(int t) {
  Int n, m;
  vector<Int> a(n), q(m);
  vector<int> cnt(n + 1), memo(n + 1, -1), ans;
  for (int i = 0; i < n; i++) {
    cnt[a[i]]++;
  }
  for (int i = 0; i < n; i++) {
    cnt[i + 1] += cnt[i];
  }
  auto f = [&](int x, int y) {
    int c = 0;
    for (int i = 0; i <= n; i += x) {
      auto j = min(n + 1, i + y);
      c += cnt[j - 1] - (i ? cnt[i - 1] : 0);
    }
    return c > n / 2;
  };
  for (auto &x : q) {
    if (memo[x] < 0) {
      memo[x] = binsearch(bind(f, x, _1), x, 0);
    }
    ans.push_back(memo[x]);
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
