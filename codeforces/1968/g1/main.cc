/**
 * https://codeforces.com/contest/1968/submission/284496556
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

struct Str : string {
  Str() { cin >> *this; }
};

struct Zfn : vector<int> {
  Zfn(auto &&a, int s = 0) : Zfn(a, s, a.size()) {}
  Zfn(auto &&a, int s, int e) : vector<int>(e - s) { // [s, e) O(n)
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      while (i + c + s < e && a[i + c + s] == a[c + s]) {
        c++, j = i; // update start of prefix
      }
    }
  }
};

constexpr auto first_false(auto &&f, auto s, auto e) { // [s, e) O(log n)
  return *ranges::partition_point(ranges::views::iota(s, e), f);
}

void solve(int t) {
  Int n, k, _;
  Str s;
  Zfn z(s);
  auto f = [&](int x) {
    int ans = 1;
    for (int i = x; i <= n - x; i++) {
      if (z[i] >= x) {
        i += x - 1;
        ans++;
      }
    }
    return ans >= k;
  };
  println(first_false(f, 1, n + 1) - 1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
