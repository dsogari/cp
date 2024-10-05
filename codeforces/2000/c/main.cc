/**
 * https://codeforces.com/contest/2000/submission/282663150
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;

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

struct SplitHash {
  size_t operator()(u64 x) const {
    x += (u64)this + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};

constexpr int lowerlatin = 'z' - 'a' + 1;

void solve(int t) {
  Int n;
  vector<Int> a(n);
  Int m;
  vector<Str> b(m);
  auto f = [&](const string &s) { // O(n)
    if (s.size() != n) {
      return false;
    }
    array<int, lowerlatin> dict;
    dict.fill(INT_MAX);
    unordered_set<int, SplitHash> used;
    for (int i = 0; i < n; i++) {
      char ch = s[i] - 'a';
      if (dict[ch] != a[i]) {
        if (dict[ch] != INT_MAX || used.contains(a[i])) {
          return false;
        }
        used.insert(a[i]);
        dict[ch] = a[i];
      }
    }
    return true;
  };
  for (auto &s : b) {
    println(f(s) ? "YES" : "NO");
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
