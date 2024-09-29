/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Cartesian Tree (using a vector)
 */
struct Treap {
  struct Info {
    int par, left, right, start, end; // [start,end) of subtree
  };
  vector<Info> nodes;
  stack<int> above; // minimum stack
  function<bool(int, int)> f;
  int top = -1;
  Treap(auto &&f) : f(f) {}
  void push(int i) { // O(1) amortized / i must be pushed in order
    assert(i == nodes.size());
    nodes.emplace_back(-1, -1, -1, i, -1);
    int last = -1;
    while (above.size() && f(above.top(), i)) {
      last = above.top();
      nodes[last].end = i;
      above.pop();
    }
    if (above.size()) {
      nodes[i].par = above.top(); // smallest greater or equal
      nodes[above.top()].right = i;
    }
    if (last >= 0) {
      nodes[last].par = i;
      nodes[i].left = last; // greatest smaller
      nodes[i].start = nodes[last].start;
    }
    if (top < 0 || f(top, i)) {
      top = i;
    }
    above.push(i);
  }
  void finish() { // O(n)
    while (!above.empty()) {
      nodes[above.top()].end = nodes.size();
      above.pop();
    }
  }
};

/**
 * Sparse Cartesian Tree
 */
template <typename T> struct SparseTreap {
  struct Info {
    T par, left, right, start, end; // [start,end] of subtree
  };
  unordered_map<T, Info> nodes;
  stack<T> above; // minimum stack
  function<bool(const T &, const T &)> f;
  const Info empty;
  T top, end, def;
  SparseTreap(auto &&f, T def) : f(f), top(def), end(def), def(def) {}
  void push(T x) { // O(1) amortized / x must be pushed in order
    assert(above.empty() || above.top() < x);
    nodes.emplace(x, Info{def, def, def, x, def});
    T last = def;
    while (above.size() && f(above.top(), x)) {
      last = above.top();
      nodes[last].end = end;
      above.pop();
    }
    if (above.size()) {
      nodes[x].par = above.top(); // smallest greater or equal
      nodes[above.top()].right = x;
    }
    if (last != def) {
      nodes[last].par = x;
      nodes[x].left = last; // greatest smaller
      nodes[x].start = nodes[last].start;
    }
    if (top == def || f(top, x)) {
      top = x;
    }
    end = x;
    above.push(x);
  }
  void finish() { // O(n)
    while (!above.empty()) {
      nodes[above.top()].end = end;
      above.pop();
    }
  }
};
