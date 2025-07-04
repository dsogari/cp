/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Minimum/Maximum Heap
 */
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

/**
 * Minimum Queue (not preserving elements)
 */
template <typename T> struct MinQueue {
  deque<T> queue;
  function<bool(const T &, const T &)> f;
  MinQueue(auto &&f) : f(f) {}
  const T &top() const { return queue.front(); } // O(1)
  void push(const T &val) {                      // O(1)
    while (queue.size() && f(val, queue.back())) {
      queue.pop_back();
    }
    queue.push_back(val);
  };
  void pop(const T &val) { // O(1)
    if (queue.size() && !f(queue.front(), val)) {
      queue.pop_front();
    }
  };
};

/**
 * Minimum Stack
 */
template <typename T> struct MinStack {
  stack<pair<T, T>> st;
  function<bool(const T &, const T &)> f;
  MinStack(auto &&f) : f(f) {}
  size_t size() const { return st.size(); };       // O(1)
  const T &top() const { return st.top().second; } // O(1)
  bool _chk(const T &val) const { return st.empty() || f(val, top()); }
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
  MinQueue2(auto &&f) : s1(f), s2(f) {}
  size_t size() const { return s1.size() + s2.size(); };                 // O(1)
  const T &top() const { return (s1.size() && _chk() ? s1 : s2).top(); } // O(1)
  bool _chk() const { return !s2.size() || s2.f(s1.top(), s2.top()); }
  void push(const T &val) { s1.push(val); } // O(1)
  T pop() {                                 // O(1)
    if (!s2.size()) {
      while (s1.size()) {
        s2.push(s1.pop());
      }
    }
    return s2.pop();
  };
};
