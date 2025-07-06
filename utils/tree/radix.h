/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Trie (N-ary prefix or suffix tree)
 */
template <typename T, size_t N> struct Trie {
  vector<pair<T, array<int, N>>> nodes;
  Trie(int cap = 1) : nodes(1) { nodes.reserve(cap); }
  void visit(auto &&f, auto &&x, auto &&...args) {
    for (int i = 0, j = 0;; j++) {
      int k = f(nodes[i], j, x, args...);
      if (k < 0) {
        break;
      }
      assert(k < N);
      auto &child = nodes[i].second[k];
      if (!child) {
        child = nodes.size();
        nodes.emplace_back(); // might invalidate references
      }
      i = nodes[i].second[k];
    }
  }
};

// Trie manipulation
const auto nodeinc = [](auto &node) { node++; };
const auto nodedec = [](auto &node) { node--; };
const auto nodeins = [](auto &node, int i) { node.insert(i); };
const auto noderem = [](auto &node, int i) { node.erase(i); };

// Trie visiting
const auto nodevis = [](auto &&fn, auto &&fx, auto &node, int j, auto &&x,
                        auto &&...args) {
  return fn(node.first, args...), fx(j, x);
};

// Bit prefixes
const auto bitpref = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << (31 - j))) != 0 : -1;
};
const auto bpinc = bind(nodevis, nodeinc, bitpref, _1, _2, _3);
const auto bpdec = bind(nodevis, nodedec, bitpref, _1, _2, _3);

// Bit suffixes
const auto bitsuff = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << j)) != 0 : -1;
};
const auto bsinc = bind(nodevis, nodeinc, bitsuff, _1, _2, _3);
const auto bsdec = bind(nodevis, nodedec, bitsuff, _1, _2, _3);

// String prefixes
const auto strpref = [](int j, auto &&s) {
  return j < s.size() ? s[j] - 'a' : -1;
};
const auto spinc = bind(nodevis, nodeinc, strpref, _1, _2, _3);
const auto spdec = bind(nodevis, nodedec, strpref, _1, _2, _3);

// String suffixes
const auto strsuff = [](int j, auto &&s) {
  return j < s.size() ? s[s.size() - j - 1] - 'a' : -1;
};
const auto ssinc = bind(nodevis, nodeinc, strsuff, _1, _2, _3);
const auto ssdec = bind(nodevis, nodedec, strsuff, _1, _2, _3);
