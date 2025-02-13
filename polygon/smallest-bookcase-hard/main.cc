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

vector<int> lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<vector<int>> seq;
  vector<int> ans;
  for (int i = s; i < e; i++) {
    if (ans.empty() || f(ans.back(), i)) {
      ans.push_back(i);
      seq.push_back({i});
    } else {
      auto j = ranges::lower_bound(ans, i, f) - ans.begin();
      ans[j] = i;
      seq[j].push_back(i);
    }
  }
  for (int i = seq.size() - 2; i >= 0; i--) {
    auto it = ranges::lower_bound(seq[i], ans[i + 1]);
    ans[i] = *prev(it);
  }
  return ans;
}

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  auto cmp1 = [&](int i, int j) { return a[i][0] < a[j][0]; };
  Iota idx(n, cmp1); // O(n*log n)
  auto cmp2 = [&](int i, int j) { return a[idx[i]][1] > a[idx[j]][1]; };
  auto seq = lis(cmp2, 0, n); // O(n*log n)
  int k = seq.size();
  vector<int> shelves;
  if (k == 1) {
    shelves.assign(n, 1);
  } else {
    vector<int> shf(n);
    vector<bool> vis(n);
    for (int j = 0; j < k; j++) { // O(k)
      vis[seq[j]] = true;
      shf[idx[seq[j]]] = j + 1;
    }
    vector<vector<int>> good(n);
    for (int i = 0; i < n; i++) { // O(n*k)
      if (vis[i]) {
        continue;
      }
      for (int j = 0; j < k; j++) {
        auto [w0, h0] = a[idx[i]];
        auto [w1, h1] = a[idx[seq[j]]];
        if ((w0 <= w1 && h0 <= h1) || (w0 >= w1 && h0 >= h1)) {
          good[i].push_back(j);
        }
      }
    }
    int ans = INT_MAX;
    vector<int> top(k), cnt(k);
    auto save = [&](int i, int j) -> array<int, 3> {
      return {exchange(top[j], a[idx[i]][1]), exchange(shf[idx[i]], j + 1),
              cnt[j]++};
    };
    auto restore = [&](int i, int j, const array<int, 3> &saved) {
      top[j] = saved[0], shf[idx[i]] = saved[1], cnt[j] = saved[2];
    };
    auto f = [&](auto &self, int i, int mx) -> void { // O({n-k,k})
      if (mx >= ans) {
        return;
      }
      if (i == n) {
        ans = mx;
        shelves = shf;
        return;
      }
      if (vis[i]) {
        return self(self, i + 1, mx);
      }
      for (auto j : good[i]) {
        if (a[idx[i]][1] >= top[j]) {
          auto saved = save(i, j);
          self(self, i + 1, max(mx, cnt[j]));
          restore(i, j, saved); // backtrack
        }
      }
    };
    f(f, 0, 0); // all valid partitions of {1,...,n} into k parts
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
