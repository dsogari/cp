/**
 * https://codeforces.com/contest/2008/submission/280751432
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
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

void solve(int t) {
  Int n;
  vector<Int> p(n);
  Str s;
  vector<int> group(n, -1), cnt;
  for (int i = 0; i < n; i++) {
    if (group[i] < 0) {
      int id = cnt.size(), c = 0;
      for (int j = i; group[j] < 0; j = p[j] - 1) {
        group[j] = id;
        c += s[j] == '0';
      }
      cnt.push_back(c);
    }
  }
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = cnt[group[i]];
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
