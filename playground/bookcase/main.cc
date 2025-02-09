/**
 * (c) 2024-2025 Diego Sogari
 */
#include "graph/graph.h"
#include "graph/tsp.h"
#include "math/order.h"

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

array<vector<int>, 2> lis2(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> inc, len;
  for (int i = s; i < e; i++) {
    if (inc.empty() || f(inc.back(), i)) {
      inc.push_back(i);
      len.push_back(1);
    } else {
      auto j = ranges::lower_bound(inc, i, f) - inc.begin();
      inc[j] = i;
      len[j]++;
    }
  }
  return {inc, len};
}

int len1(auto &&b, int n, int k) { // O({k,n}) = O(k^n/k!), Stirling number
  vector<int> s(k), c(k);
  auto f = [&](auto &self, int i) -> int {
    if (i == n) {
      return ranges::max(c);
    }
    int ans = INT_MAX;
    for (int j = 0; j < k; j++) {
      if (s[j] <= b[i][1]) {
        auto saved = s[j];
        s[j] = b[i][1], c[j]++;
        ans = min(ans, self(self, i + 1));
        s[j] = saved, c[j]--; // backtrack
        if (!s[j]) {
          break; // no need to go further
        }
      }
    }
    return ans;
  };
  return f(f, 0); // all partitions of {1,...,n} into k
}

int len2(auto &&b, int n, int k, int mxlen) { // O({k,n}) = O(k^n/k!)
  Digraph g(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (b[i][1] <= b[j][1]) {
        g.add(i, j);
      }
    }
  }
  vector<bool> vis(n);
  auto f = [&](int len) {
    auto dfs = [&](auto &self, int u, int i, int j) -> bool {
      vis[u] = true;
      if (j < len) {
        for (auto &&v : g[u]) {
          if (!vis[v] && self(self, v, i, j + 1)) {
            vis[u] = false;
            return true;
          }
        }
      }
      bool ans = true;
      auto v = ranges::find(vis, false) - vis.begin();
      if (v < n) {
        ans = i < k && self(self, v, i + 1, 1);
      } else {
        assert(i == k);
      }
      vis[u] = false;
      return ans;
    };
    return !dfs(dfs, 0, 1, 1);
  };
  assert(k > 0 && k <= n);
  return first_false(f, n / k, mxlen + 1);
}

int len3(auto &&b, int n, int k, int mxlen) { // O(4^n*log n)
  vector<bool> memo(1 << n);
  for (int i = 0; i < n; i++) {
    memo[1 << i] = true;
  }
  for (unsigned i = 1; i < 1 << n; i++) { // O(n*2^n)
    if (memo[i]) {
      auto l = bit_width(i) - 1;
      for (int r = l + 1; r < n; r++) {
        if (b[l][1] <= b[r][1]) {
          memo[i | 1 << r] = true;
        }
      }
    }
  }
  vector<int> dp(1 << n);
  auto f = [&](int len) {                   // O(4^n)
    for (unsigned i = 1; i < 1 << n; i++) { // O(n*2^n)
      dp[i] = memo[i] && popcount(i) <= len ? 1 : INT_MAX;
    }
    for (unsigned i = 1; i < 1 << n; i++) { // O(4^n)
      if (dp[i] < INT_MAX) {
        auto l = bit_width(i);
        for (unsigned j = 1 << l; j < 1 << n; j++) {
          if (!(i & j) && dp[j] < INT_MAX) {
            dp[i | j] = min(dp[i | j], dp[i] + dp[j]);
          }
        }
      }
    }
    assert(dp.back() < INT_MAX);
    return dp.back() > k;
  };
  assert(k > 0 && k <= n);
  return first_false(f, n / k, mxlen + 1);
}

void solve(int t) {
  Int n;
  vector<array<Int, 2>> b(n);
  // int n = 18;
  // vector<array<int, 2>> b(n);
  // for (auto &&bi : b) {
  //   bi[0] = rand() % (2 * n) + 1;
  //   bi[1] = rand() % (2 * n) + 1;
  // }
  ranges::sort(b); // O(n*log n)
  auto cmp = [&](int i, int j) { return b[i][1] > b[j][1]; };
  auto [seq, cnt] = lis2(cmp, 0, n); // O(n*log n)
  int k = seq.size(), mxlen = *ranges::max_element(cnt);
  auto t0 = now();
  int l1 = len1(b, n, k);
  auto t1 = now();
  int l2 = len2(b, n, k, mxlen);
  auto t2 = now();
  int l3 = len3(b, n, k, mxlen);
  auto t3 = now();
  assert(l1 == l2);
  assert(l1 == l3);
  chrono::duration<double, milli> d1 = t1 - t0, d2 = t2 - t1, d3 = t3 - t2;
  println(b, "\e[80G", k, l1, l2, l3, d1.count(), d2.count(), d3.count());
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  // srand(time(0));
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
