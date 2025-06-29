/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "graph/graph.h"

struct NodeInfo {
  int tin, tout, dep, siz, hei, diam, far1, far2;
  vector<int> par; // binary lifting
};

/**
 * Subtree information
 */
struct Subtree : vector<NodeInfo> {
  Subtree(const Graph &g, int s, int t = 0) : vector<NodeInfo>(g.size()) {
    dfs(g, s, s, t);
  }
  void dfs(const Graph &g, int u, int p, int &t, int d = 1) { // O(n*log n)
    auto &cur = (*this)[u] = {++t, 0, d, 1, 1, 1, u, u};
    cur.par.assign(bit_width(g.size()), p);
    for (int i = 1; i < cur.par.size(); ++i) {
      cur.par[i] = (*this)[cur.par[i - 1]].par[i - 1];
    }
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, v, u, t, d + 1);
        auto &child = (*this)[v];
        cur.siz += child.siz;
        if (cur.diam < cur.hei + child.hei) {
          cur.diam = cur.hei + child.hei;
          cur.far2 = child.far1;
          if (cur.hei <= child.hei) {
            ::swap(cur.far1, cur.far2);
            cur.hei = child.hei + 1;
          }
        }
        if (cur.diam < child.diam) {
          cur.diam = child.diam;
          cur.far1 = child.far1;
          cur.far2 = child.far2;
        }
      }
    }
    cur.tout = ++t;
  }
  int dist(int u, int v) { // O(log n)
    return (*this)[u].dep + (*this)[v].dep - 2 * (*this)[lca(u, v)].dep;
  }
  int lca(int u, int v) const { // O(log n)
    return _isanc(u, v) ? u : _isanc(v, u) ? v : _find(u, v);
  }
  bool _isanc(int u, int v) const { // O(1)
    auto &a = (*this)[u], &b = (*this)[v];
    return a.tin <= b.tin && a.tout >= b.tout;
  }
  int _find(int u, int v) const { // O(log n)
    for (int i = (*this)[u].par.size() - 1; i >= 0; i--) {
      if (!_isanc((*this)[u].par[i], v)) {
        u = (*this)[u].par[i];
      }
    }
    return (*this)[u].par[0];
  }
  int _from(int u, int k) const { // O(log n)
    for (int i = 0; i < (*this)[u].par.size(); i++) {
      if (k & (1 << i)) {
        u = (*this)[u].par[i];
      }
    }
    return u;
  }
  int kth(int u, int v, int k) { // O(log n)
    int a = lca(u, v);
    int ua = (*this)[u].dep - (*this)[a].dep;
    int va = (*this)[v].dep - (*this)[a].dep;
    return k <= ua ? _from(u, k) : _from(v, ua + va - k);
  }
};