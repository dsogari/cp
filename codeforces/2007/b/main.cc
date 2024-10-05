/**
 * https://codeforces.com/contest/2007/submission/280245432
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;

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
using Chr = Num<char>;

struct Query {
  Chr type;
  Int l, r;
};

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  vector<Query> q(m);
  vector<int> ans;
  auto mx = *ranges::max_element(a);
  for (auto &&[type, l, r] : q) {
    if (l <= mx && mx <= r) {
      mx += type == '+' ? 1 : -1;
    }
    ans.push_back(mx);
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
