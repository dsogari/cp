/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Maximum (function object)
 */
template <typename T> struct Max {
  T operator()(const T &lhs, const T &rhs) const { return max(lhs, rhs); }
};

/**
 * Minimum (function object)
 */
template <typename T> struct Min {
  T operator()(const T &lhs, const T &rhs) const { return min(lhs, rhs); }
};

/**
 * Vector Indices
 */
struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

/**
 * Binary Search
 */
int binsearch(auto &&f, int s, int e) { // [s, e) O(log n)
  for (int inc = s < e ? 1 : -1; s != e;) {
    auto m = midpoint(s, e);
    f(m) ? s = m + inc : e = m;
  }
  return s; // first such that f is false
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
  vector<int> ans;
  for (int i = s; i < e; i++) {
    if (ans.empty() || f(ans.back(), i)) {
      ans.push_back(i);
    } else {
      *ranges::lower_bound(ans, i, f) = i;
    }
  }
  return ans;
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

// Comparison operators
const less<int> lt1;
const greater<int> gt1;
const equal_to<int> eq1;
const less<array<int, 2>> lt2;
const greater<array<int, 2>> gt2;
const equal_to<array<int, 2>> eq2;

// Custom comparison
const auto lta1 = [](auto &lhs, auto &rhs) { return lhs[0] < rhs[0]; };
const auto gta1 = [](auto &lhs, auto &rhs) { return lhs[0] > rhs[0]; };
const auto lta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
};
const auto gta2 = [](auto &lhs, auto &rhs) {
  return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
};

// Utility functions
// sort
// nth_element
// next_permutation
