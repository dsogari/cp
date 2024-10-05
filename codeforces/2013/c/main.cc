/**
 * https://codeforces.com/contest/2013/submission/282646934
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

int simulate(const string &pass, const string &s) {
  return pass.find(s) != string::npos;
}

void solve(int t) {
  Int n;
#ifndef ONLINE_JUDGE
  Str pass;
#endif
  int rem = 2 * n;
  auto query = [&](const string &s) {
    assert(rem--);
    println('?', s);
#ifndef ONLINE_JUDGE
    return simulate(pass, s);
#else
    return Int();
#endif
  };
  string ans;
  auto f = [&](const string &s) {
    auto r = query(s);
    assert(r >= 0);
    if (r > 0) {
      ans = s;
    }
    return r;
  };
  bool right = false;
  while (ans.size() < n) {
    if (!right) {
      if (f(ans + "0") || f(ans + "1")) {
        continue;
      }
      right = true;
    }
    if (f("0" + ans)) {
      continue;
    }
    ans = "1" + ans;
  }
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
