/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Median Queue (using one set)
 */
template <typename T> struct MedQueue {
  function<bool(const T &, const T &)> f;
  multiset<T, decltype(f)> set;
  decltype(set)::iterator mid;
  MedQueue(auto &&f) : f(f), set(f), mid(set.end()) {}
  size_t size() const { return set.size(); }; // O(1)
  const T &top() const { return *mid; }       // O(1)
  int _inc(const T &val) {
    return size() == 1 ? -1 : size() % 2 - f(val, *mid);
  }
  void push(const T &val) { // O(log n)
    set.insert(val);
    mid = next(mid, _inc());
  }
  void pop(const T &val) { // O(log n)
    mid = next(mid, -_inc());
    auto it = set.find(val);
    assert(it != set.end());
    set.erase(it);
  }
};

/**
 * Median Queue (using two sets)
 */
template <typename T> struct MedQueue2 {
  function<bool(const T &, const T &)> f;
  multiset<T, decltype(f)> s1, s2;
  MedQueue(auto &&f) : f(f), s1(bind(f, _2, _1)), s2(f) {}
  size_t size() const { return s1.size() + s2.size(); }; // O(1)
  const T &top() const { return *s1.begin(); }           // O(1)
  bool _chk(const T &val) const { return !s2.size() || f(val, *s2.begin()); }
  void push(const T &val) { // O(log n)
    (_chk(val) ? s1 : s2).insert(val);
    _rebalance();
  }
  void pop(const T &val) { // O(log n)
    auto &set = _chk(val) ? s1 : s2;
    auto it = set.find(val);
    assert(it != set.end());
    set.erase(it);
    _rebalance();
  }
  void _rebalance() { // O(1)
    if (s1.size() > s2.size() + 1) {
      s2.insert(s2.begin(), s1.extract(s1.begin()));
    } else if (s1.size() < s2.size()) {
      s1.insert(s1.begin(), s2.extract(s2.begin()));
    }
  }
};
