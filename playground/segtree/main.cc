/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#include "debug.h"
#include "math/pref.h"
#include "tree/segment.h"
init();

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

struct Lazy {
  bool add;
  int val;
  operator int() const { return val; }
  Lazy join(const Lazy &rhs) const {
    return {rhs.add, rhs.add == 'a' ? val + rhs.val : rhs.val};
  }
};

void solve(int t) {
  Int n;
  PushSegTree<int, Lazy> segtree(n, tadd, tadd, &Lazy::join);

  println("OK");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
