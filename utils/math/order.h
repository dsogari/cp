/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

template <typename T> T imin(T x, T y) { return min(x, y); }
template <typename T> T imax(T x, T y) { return max(x, y); }

/**
 * Maximum Heap
 */
template <typename T, typename F = less<T>>
using MaxHeap = priority_queue<T, F>;

/**
 * Minimum Heap
 */
template <typename T, typename F = greater<T>>
using MinHeap = priority_queue<T, vector<T>, F>;

/**
 * Element Indices
 */
struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
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

/**
 * Minimum Queue (not preserving elements)
 */
template <typename T> struct MinQueue {
  deque<T> queue;
  bool empty() const { return queue.empty(); }   // O(1)
  const T &top() const { return queue.front(); } // O(1)
  void push(const T &val) {                      // O(1) amortized
    while (queue.size() && val < queue.back()) {
      queue.pop_back();
    }
    queue.push_back(val);
  };
  void pop(const T &val) { // O(1)
    if (queue.size() && val <= queue.front()) {
      queue.pop_front();
    }
  };
};

/**
 * Minimum Stack
 */
template <typename T> struct MinStack {
  stack<pair<T, T>> st;
  size_t size() const { return st.size(); };       // O(1)
  const T &top() const { return st.top().second; } // O(1)
  bool _chk(const T &val) const { return st.empty() || val < top(); }
  void push(const T &val) { st.emplace(val, _chk(val) ? val : top()); }; // O(1)
  T pop() {                                                              // O(1)
    auto val = st.top().first;
    return st.pop(), val;
  };
};

/**
 * Minimum Queue (preserving elements)
 */
template <typename T> struct MinQueue2 {
  MinStack<T> s1, s2;
  size_t size() const { return s1.size() + s2.size(); };                 // O(1)
  const T &top() const { return (s1.size() && _chk() ? s1 : s2).top(); } // O(1)
  bool _chk() const { return !s2.size() || s1.top() < s2.top(); }
  void push(const T &val) { s1.push(val); } // O(1)
  T pop() {                                 // O(1) amortized
    if (!s2.size()) {
      while (s1.size()) {
        s2.push(s1.pop());
      }
    }
    return s2.pop();
  };
};
