/**
 * https://codeforces.com/contest/2003/submission/278118791
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

void solve(int t) { // O(n + A*log A), A is the size of the alphabet
  Int n;
  Str s;
  map<char, int> cnt;
  for (auto &&c : s) { // O(A*log A)
    cnt[c]++;
  }
  string ans;
  while (cnt.size()) { // O(n)
    for (auto it = cnt.begin(); it != cnt.end();) {
      ans.push_back(it->first);                     // O(1) amortized
      it = --it->second ? next(it) : cnt.erase(it); // O(1) amortized
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
