/**
 * https://codeforces.com/contest/2117/submission/323498009
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
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

void solve(int t) {
  Int n;
  vector<Int> a(n), b(n);
  map<int, int> count;
  int i = n - 1;
  for (; i >= 0; i--) {
    if (a[i] == b[i]) {
      break;
    }
    auto &ca = count[a[i]];
    auto &cb = count[b[i]];
    if (ca > 1 || cb > 1) {
      break;
    }
    if (ca == 1 && i < n - 1 && a[i] != b[i + 1]) {
      break;
    }
    if (cb == 1 && i < n - 1 && b[i] != a[i + 1]) {
      break;
    }
    ca++, cb++;
  }
  auto ans = i + 1;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
