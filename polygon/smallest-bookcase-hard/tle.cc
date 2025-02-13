/**
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

int llis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> ans;
  for (int i = s; i < e; i++) {
    if (ans.empty() || f(ans.back(), i)) {
      ans.push_back(i);
    } else {
      *ranges::lower_bound(ans, i, f) = i;
    }
  }
  return ans.size();
}

constexpr auto first_false(auto &&f, auto s, auto e) { // [s, e) O(log n)
  return *ranges::partition_point(ranges::views::iota(s, e), f);
}

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  auto cmp1 = [&](int i, int j) { return a[i] < a[j]; };
  Iota idx(n, cmp1); // O(n*log n)
  auto cmp2 = [&](int i, int j) { return a[idx[i]][1] > a[idx[j]][1]; };
  int k = llis(cmp2, 0, n); // O(n*log n)
  vector<int> shelves(n);
  if (k == 1) {
    shelves.assign(n, 1);
  } else {
    vector<bool> memo(1 << n);
    for (int i = 0; i < n; i++) {
      memo[1 << i] = true;
    }
    for (unsigned i = 1; i < 1 << n; i++) { // O(n*2^n)
      if (memo[i]) {
        auto l = bit_width(i) - 1;
        for (int r = l + 1; r < n; r++) {
          if (a[idx[l]][1] <= a[idx[r]][1]) {
            memo[i | 1 << r] = true;
          }
        }
      }
    }
    vector<int> dp(1 << n);
    vector<array<unsigned, 2>> par(1 << n), par2 = par;
    auto f = [&](int len) {                   // O(4^n)
      for (unsigned i = 1; i < 1 << n; i++) { // O(n*2^n)
        dp[i] = memo[i] && popcount(i) <= len ? 1 : INT_MAX;
      }
      for (unsigned i = 1; i < 1 << n; i++) { // O(4^n)
        if (dp[i] < INT_MAX) {
          auto l = bit_width(i);
          for (unsigned j = 1 << l; j < 1 << n; j++) {
            if (!(i & j) && dp[j] < INT_MAX && dp[i] + dp[j] < dp[i | j]) {
              dp[i | j] = dp[i] + dp[j];
              par[i | j] = {i, j};
            }
          }
        }
      }
      assert(dp.back() < INT_MAX);
      if (dp.back() <= k) {
        swap(par, par2);
      }
      return dp.back() > k;
    };
    assert(k > 0 && k <= n);
    first_false(f, n / k, n + 1);      // O(4^n*log n)
    auto f1 = [&](int mask, int num) { // O(n)
      for (int j = 0; j < n; j++) {
        if (mask & 1 << j) {
          shelves[idx[j]] = num;
        }
      }
    };
    for (unsigned i = (1 << n) - 1, s = 1; i;) { // O(n*2^n)
      auto [u, v] = par2[i];
      if (u > 0 && memo[u]) {
        f1(u, s++);
      }
      if (v > 0 && memo[v]) {
        f1(v, s++);
      }
      i = u > 0 && !memo[u] ? u : v;
    }
  }
  println(k);
  println(shelves);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
