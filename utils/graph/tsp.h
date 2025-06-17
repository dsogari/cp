/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Traveling Salesman Problem (without starting point)
 */
template <typename T> struct TSP : vector<vector<T>> {
  TSP(const vector<vector<T>> &g) : TSP(g, g.size()) {}
  TSP(const vector<vector<T>> &g, int n)
      : vector<vector<T>>(n, vector<T>(1u << n, numeric_limits<T>::max())) {
    assert(n < 32);
    for (int i = 0; i < n; i++) {
      (*this)[i][1 << i] = {}; // shortest path ending at i, including i
    }
    for (int i = 1; i < 1u << n; i++) { // all subsets in increasing size
      for (int j = 0; j < n; j++) {     // select last node in path
        if (i & 1 << j) {               // last node is in subset?
          for (int k = 0; k < n; k++) { // select next node in path
            if (~i & 1 << k) {          // next node is not in subset?
              auto &next = (*this)[k][i | 1 << k];
              next = min(next, (*this)[j][i] + g[j][k]);
            }
          }
        }
      }
    }
  }
};

/**
 * Traveling Salesman Problem (with starting point)
 */
template <typename T> struct TSPPlus : vector<vector<T>> {
  vector<vector<int>> start;
  TSPPlus(const vector<vector<T>> &g) : TSPPlus(g, g.size()) {}
  TSPPlus(const vector<vector<T>> &g, int n)
      : vector<vector<T>>(n, vector<T>(1u << n, numeric_limits<T>::max())),
        start(n, vector<int>(1u << n)) {
    assert(n < 32);
    for (int i = 0; i < n; i++) {
      (*this)[i][1 << i] = {}; // shortest path ending at i, including i
      start[i][1 << i] = i;    // starting at i
    }
    for (int i = 1; i < 1u << n; i++) { // all subsets in increasing size
      for (int j = 0; j < n; j++) {     // select last node in path
        if (i & 1 << j) {               // last node is in subset?
          for (int k = 0; k < n; k++) { // select next node in path
            if (~i & 1 << k) {          // next node is not in subset?
              auto &next = (*this)[k][i | 1 << k];
              auto value = (*this)[j][i] + g[j][k];
              if (value < next) {
                next = value;
                start[k][i | 1 << k] = start[j][i];
              }
            }
          }
        }
      }
    }
  }
};
