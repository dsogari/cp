/**
 * https://codeforces.com/contest/2014/submission/282696711
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
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

void solve(int t) {
  Int n, m, k;
  vector<array<Int, 2>> da(n);
  vector<int> expiry = {0};
  vector<i64> milk = {0};
  int ans = 0;
  auto f = [&](int day) { // O(log k)
    auto sum = milk.back();
    auto i = ranges::upper_bound(expiry, day) - expiry.begin();
    auto j = ranges::upper_bound(milk, sum - m) - milk.begin();
    if (i <= j && j < milk.size()) {
      milk[j] = sum - m;
      if (milk[j] > milk[j - 1]) {
        j++;
      }
      ans++;
    } else {
      j = 1;
    }
    expiry.resize(j);
    milk.resize(j);
  };
  int day = 1, mx = 0;
  for (auto [d, c] : da) { // O(n*log k)
    while (day < d && milk.size() > 1) {
      f(day++);
    }
    day = d;
    expiry.push_back(d + k);
    milk.push_back(milk.back() + c);
    mx = d + k;
  }
  while (day < mx && milk.size() > 1) {
    f(day++);
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
