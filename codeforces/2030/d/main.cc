/**
 * https://codeforces.com/contest/2030/submission/286825436
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
  if (ranges::is_sorted(p)) {
    for (int i = 0; i < m; i++) {
      println("YES");
    }
    return;
  }
  vector<int> mx(n), mn(n);
  mx[0] = p[0];
  mn[n - 1] = p[n - 1];
  for (int i = 1, j = n - 2; i < n; i++, j--) {
    mx[i] = max(mx[i - 1], +p[i]);
    mn[j] = min(mn[j + 1], +p[j]);
  }
  vector<bool> bad(n);
  int badcnt = 0;
  for (int i = 1; i < n; i++) {
    bad[i] = s[i - 1] == 'L' && s[i] == 'R' && mx[i - 1] > mn[i];
    badcnt += bad[i];
  }
  for (auto &&i : q) {
    i--;
    badcnt -= bad[i] + bad[i + 1];
    s[i] = s[i] == 'L' ? 'R' : 'L';
    bad[i] = s[i - 1] == 'L' && s[i] == 'R' && mx[i - 1] > mn[i];
    bad[i + 1] = s[i] == 'L' && s[i + 1] == 'R' && mx[i] > mn[i + 1];
    badcnt += bad[i] + bad[i + 1];
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
