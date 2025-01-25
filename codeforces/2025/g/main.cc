/**
 * https://codeforces.com/contest/2025/submission/302834799
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

struct Block {
  vector<i64> pref; // sum of scores for each starting balance
  int size, shift;  // current shift in balance at end of block
  Block(int s) : pref(2 * s + 1), size(s), shift(0) {}
  void update(int l, int r, auto &&get) { // O(s)
    pref.assign(2 * size + 1, 0);
    shift = 0;
    for (int i = l; i < r; i++) { // O(s)
      auto [type, val] = get(i);
      if (type == 1) {
        pref[0] += val * 2;
        pref[size - shift] -= val; // maximum starting balance (-shift-1)
        shift++;
      } else if (type == 2) {
        pref[size - shift + 1] += val; // minimum starting balance (-shift+1)
        shift--;
      }
    }
    for (int i = 0; i < 2 * size; i++) { // O(s)
      pref[i + 1] += pref[i];
    }
  }
  i64 get(int bal) const { return pref[max(0, min(2 * size, size + bal))]; }
};

void solve(int t) {
  Int q;
  vector<array<Int, 2>> a(q);
  auto cmp = [&](int i, int j) { return a[i][1] > a[j][1]; };
  Iota idx(q, cmp); // O(q*log q)
  vector<int> ridx(q);
  for (int i = 0; i < q; i++) { // O(q)
    ridx[idx[i]] = i;
  }
  auto get = [&](int i) {
    return ridx[idx[i]] < 0 ? a[idx[i]] : array<Int, 2>{0, 0};
  };
  int s = sqrt(q + 10);
  vector blocks((q + s - 1) / s, Block(s)); // O(q)
  for (auto &i : ridx) {                    // O(q*sqrt q)
    auto j = exchange(i, -1);               // activate
    auto l = j - j % s, r = min(l + s, +q);
    blocks[j / s].update(l, r, get);
    i64 ans = 0;
    int bal = 0;
    for (auto &block : blocks) {
      ans += block.get(bal);
      bal += block.shift;
    }
    println(ans);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
#ifdef ONLINE_JUDGE
  int t = 1;
#else
  Int t;
#endif
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
