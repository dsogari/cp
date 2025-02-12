/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Element Indices
 */
struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

/**
 * Element Frequencies
 */
struct Freq : vector<int> {
  Freq(const auto &a) : Freq(a, ranges::max(a)) {}
  Freq(const auto &a, int mx) : vector<int>(mx + 1) { // O(n)
    for (auto &&ai : a) {
      (*this)[ai]++;
    }
  }
};

/**
 * Binary Search (first such that f is false)
 */
constexpr auto first_false(auto &&f, auto s, auto e) { // [s, e) O(log n)
  return *ranges::partition_point(ranges::views::iota(s, e), f);
}

/**
 * Binary Search (for real numbers)
 */
double binsearch(auto &&f, double s, double e, int iter) {
  while (iter--) {
    auto m = (s + e) / 2;
    (f(m) ? s : e) = m;
  }
  return (s + e) / 2;
}

/**
 * Longest Increasing Subsequence
 */
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

/**
 * Length of the Longest Increasing Subsequence
 */
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

/**
 * Maximum Sum of Subsequences of Length R Mod K
 * A good subsequence is one where there are a multiple of k elements in between
 * any 2 elements.
 * @see https://cfstep.com/codeforces/contests/contest-1993/problem-d/code/
 */
int max_sum_subseq_mod_k(const vector<int> &a, int k, int r) {
  vector<int> dp(k + 1);
  for (int i = 0; i < a.size(); i++) {
    int len = 1 + i % k;
    dp[len] = max(dp[len], dp[len - 1] + a[i]);
  }
  return dp[r];
}

/**
 * Inversion Count
 */
int invcount(auto &&f, int s, int e) { // [s, e) O(n^2)
  int ans = 0;
  for (int i = s; i < e; i++) {
    for (int j = i + 1; j < e; j++) {
      ans += f(j, i);
    }
  }
  return ans;
}

/**
 * Cyclic Shift (of sorted array, rightwise)
 */
int cyclicshift(auto &&f, int s, int e) { // [s, e) O(n)
  int ans = 0;
  for (int i = s + 1; i < e; i++) {
    if (f(i, i - 1)) {
      if (ans) {
        return -1; // array must contain at most one such inversion
      }
      ans = i;
    }
  }
  return ans && s < e - 2 && f(s, e - 1) ? -1 : ans;
}
