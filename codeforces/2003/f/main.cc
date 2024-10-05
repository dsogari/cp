/**
 * https://codeforces.com/contest/2003/submission/282687765
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u32 = uint32_t;
using u64 = uint64_t;

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

template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
};

template <typename T> struct Max {
  T operator()(const T &lhs, const T &rhs) const { return max(lhs, rhs); }
};

struct PCG {
  u64 state, inc;
  PCG(u64 seed) : PCG(seed, (u64)this << 1u | 1u) {}
  PCG(u64 seed, u64 seq) : state(0), inc(seq) { step(), state += seed, step(); }
  u32 operator()() { // O(1)
    auto ans = rotr<u32>(((state >> 18u) ^ state) >> 27u, state >> 59u);
    return step(), ans;
  }
  void step() { state = state * 6364136223846793005ull + inc; } // O(1)
};

auto now() { return chrono::high_resolution_clock::now(); }

#ifdef ONLINE_JUDGE
constexpr auto limit = 1.9;
#else
constexpr auto limit = 0.1;
#endif

void solve(int t) {
  Int n, m;
  vector<Int> a(n), b(n), c(n);
  vector<int> ids(n);
  PCG rng(now().time_since_epoch().count());
  int ans = -1;
  for (auto s = now(); chrono::duration<double>(now() - s).count() < limit;) {
    for (auto &&id : ids) {
      id = rng() % m;
    }
    vector dp(m - 1, FenTree<int>(n, Max<int>{}, -1));
    for (int i = 0; i < n; i++) {
      auto ord = ids[b[i] - 1];
      auto val = ord ? dp[ord - 1].query(a[i] - 1) : 0;
      if (val >= 0) {
        if (ord < m - 1) {
          dp[ord].update(a[i] - 1, val + c[i]);
        } else {
          ans = max(ans, val + c[i]);
        }
      }
    }
  }
  println(ans);
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
