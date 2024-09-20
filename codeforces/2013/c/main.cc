/**
 * https://codeforces.com/contest/2013/submission/282080555
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

struct Str : string {
  Str() { cin >> *this; }
};

int simulate(const string &pass, const string &s) {
  return pass.find(s) != string::npos;
}

mt19937 rng(random_device{}());

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
  bool right = false;
  while (ans.size() < n) {
    if (!right) {
      auto r = query(ans + "0");
      if (r < 0) {
        return;
      }
      if (r) {
        ans += "0";
        continue;
      }
      r = query(ans + "1");
      if (r < 0) {
        return;
      }
      if (r) {
        ans += "1";
        continue;
      }
      right = true;
    }
    auto r = query("0" + ans);
    if (r < 0) {
      return;
    }
    if (r) {
      ans = "0" + ans;
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
