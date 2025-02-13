/**
 * (c) 2024-2025 Diego Sogari
 */
#include "graph/graph.h"
#include "math/order.h"

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

int len1(auto &&b, int n, int k, auto &&seq, auto &&shelves) { // O({n-k,k})
  if (k == 1) {
    return n;
  }
  vector<int> shf(n);
  vector<bool> vis(n);
  for (int j = 0; j < k; j++) { // O(k)
    vis[seq[j]] = true;
    shf[seq[j]] = j + 1;
  }
  vector<vector<int>> good(n);
  for (int i = 0; i < n; i++) { // O(n*k)
    if (vis[i]) {
      continue;
    }
    for (int j = 0; j < k; j++) {
      auto [w0, h0] = b[i];
      auto [w1, h1] = b[seq[j]];
      if ((w0 <= w1 && h0 <= h1) || (w0 >= w1 && h0 >= h1)) {
        good[i].push_back(j);
      }
    }
  }
  int ans = INT_MAX;
  // int pass1 = 0, pass2 = 0, pass3 = 0;
  vector<int> top(k), cnt(k);
  auto save = [&](int i, int j) -> array<int, 3> {
    return {exchange(top[j], b[i][1]), exchange(shf[i], j + 1), cnt[j]++};
  };
  auto restore = [&](int i, int j, const array<int, 3> &saved) {
    top[j] = saved[0], shf[i] = saved[1], cnt[j] = saved[2];
  };
  auto f = [&](auto &self, int i, int mx) -> void { // O({n-k,k})
    if (mx >= ans) {
      // pass1++;
      return;
    }
    if (i == n) {
      // pass2++;
      ans = mx;
      shelves = shf;
      return;
    }
    if (vis[i]) {
      return self(self, i + 1, mx);
    }
    // pass3++;
    for (auto j : good[i]) {
      if (b[i][1] >= top[j]) {
        auto saved = save(i, j);
        self(self, i + 1, max(mx, cnt[j]));
        restore(i, j, saved); // backtrack
      }
    }
  };
  f(f, 0, 0); // all valid partitions of {1,...,n} into k parts
  // debug(pass1, pass2, pass3);
  return ans + 1;
}

void solve(int t) {
  Int n;
  vector<array<Int, 2>> b(n);
  // int n = 20;
  // vector<array<int, 2>> b(n);
  // for (auto &&bi : b) {
  //   bi[0] = rand() % 10000 + 1;
  //   bi[1] = rand() % 10000 + 1;
  // }
  ranges::sort(b); // O(n*log n)
  auto cmp = [&](int i, int j) { return b[i][1] > b[j][1]; };
  auto seq = lis(cmp, 0, n);
  int k = seq.size(); // O(n*log n)
  auto t0 = now();
  vector<int> shelves;
  int l1 = len1(b, n, k, seq, shelves);
  auto t1 = now();
  chrono::duration<double, milli> d1 = t1 - t0;
  println(b, seq, shelves, k, l1, d1.count());
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  // srand(time(0));
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
