/**
 * https://codeforces.com/contest/2025/submission/285887322
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

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  map<int, int> cnt;
  for (auto &&ai : a) { // O(n*log n)
    cnt[ai]++;
  }
  list<int> window;
  int ans = 0, cur = 0, prev = 0;
  for (auto &&[ai, c] : cnt) { // O(n)
    if (prev == 0 || ai == prev + 1) {
      window.push_back(c);
      cur += c;
      if (window.size() > k) {
        cur -= window.front();
        window.pop_front();
      }
    } else {
      window = {c};
      cur = c;
    }
    ans = max(ans, cur);
    prev = ai;
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
