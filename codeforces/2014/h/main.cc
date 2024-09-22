/**
 * https://codeforces.com/contest/2014/submission/282504837
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

mt19937 rng(random_device{}());

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  unordered_map<int, int> ids;
  vector<array<Int, 2>> q(m);
  vector<int> pref(n + 1);
  for (int i = 0; i < n; i++) { // O(n)
    if (!ids.contains(a[i])) {
      ids[a[i]] = rng();
    }
    pref[i + 1] = pref[i] ^ ids[a[i]];
  }
  for (auto &&[l, r] : q) { // O(m)
    auto ans = (r - l + 1) % 2 || pref[r] ^ pref[l - 1] ? "NO" : "YES";
    println(ans);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
