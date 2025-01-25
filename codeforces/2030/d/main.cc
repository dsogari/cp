/**
 * https://codeforces.com/contest/2030/submission/286827040
 *
 * Permutation; sorting
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
  using string::string;
  Str() { cin >> *this; }
};

void solve(int t) {
  Int n, m;
  vector<Int> p(n);
  Str s;
  vector<Int> q(m);
  if (ranges::is_sorted(p)) {     // O(n)
    for (int i = 0; i < m; i++) { // O(m)
      println("YES");
    }
    return;
  }
  vector<int> mx(n);
  mx[0] = p[0];
  for (int i = 1; i < n; i++) { // O(n)
    mx[i] = max(mx[i - 1], +p[i]);
  }
  auto f = [&](int i) {
    return s[i - 1] == 'L' && s[i] == 'R' && mx[i - 1] > i;
  };
  int badcnt = 0;
  for (int i = 1; i < n; i++) { // O(n)
    badcnt += f(i);
  }
  for (auto &&i : q) { // O(m)
    i--;
    badcnt -= f(i) + f(i + 1);
    s[i] = s[i] == 'L' ? 'R' : 'L';
    badcnt += f(i) + f(i + 1);
    auto ans = badcnt ? "NO" : "YES";
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
