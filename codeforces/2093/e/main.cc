/**
 * https://codeforces.com/contest/2093/submission/327597148
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

constexpr auto first_false(auto &&f, auto s, auto e) { // [s, e) O(log n)
  return *ranges::partition_point(ranges::views::iota(s, e), f);
}

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  auto f = [&](int mex) { // O(n)
    int ans = 0;
    vector<int> seen(mex);
    for (int i = 0, size = 0; i < n; i++) {
      if (a[i] >= mex) {
        continue; // skip elements not less than mex
      }
      if (seen[a[i]] == ans) {
        size++;
        seen[a[i]]++; // mark element as seen
      }
      if (size == mex) {
        ans++;
        size = 0;
      }
    }
    return ans >= k;
  };
  auto ans = first_false(f, 1, n + 1) - 1;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
