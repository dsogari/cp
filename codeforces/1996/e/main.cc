/**
 * https://codeforces.com/contest/1996/submission/284706660
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

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

template <typename T, auto M> struct Mod {
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  static V inv(V x, V m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  make_unsigned_t<T> x;
  Mod() : x(0) {}
  Mod(auto y) : x(y % M) { x >= M ? x += M : x; }
  operator T() const { return x; }
  Mod operator-() const { return Mod() -= *this; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return (x += rhs.x) >= M ? x -= M : x, *this; }
  Mod &operator-=(Mod rhs) { return (x -= rhs.x) >= M ? x += M : x, *this; }
  Mod &operator*=(Mod rhs) { return x = x * V(rhs.x) % M, *this; }
  Mod &operator/=(Mod rhs) { return x = x * inv(rhs.x, M) % M, *this; }
};
using Mint = Mod<int, 1000000007>;

void solve(int t) {
  Str s;
  int n = s.size();
  vector<int> sum(n + 1); // will hold values in the range [-n,n]
  for (int i = 0; i < n; i++) {
    sum[i + 1] += sum[i] + 2 * (s[i] - '0') - 1;
  }
  vector<vector<int>> idx_by_sum(2 * n + 1); // will hold 1-based indices
  for (int i = 0; i <= n; i++) {
    idx_by_sum[sum[i] + n].push_back(i);
  }
  Mint ans = 0;
  for (auto &idx : idx_by_sum) { // O(n) because there are at most n indices
    int m = idx.size();
    vector<Mint> cnt(m); // one less, because the first index doesn't count
    for (int i = 0; i < m - 1; i++) {
      cnt[i + 1] += cnt[i] + n - idx[i + 1] + 1;
    }
    for (int i = 0; i < m - 1; i++) {
      ans += (cnt.back() - cnt[i]) * (idx[i] + 1);
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
