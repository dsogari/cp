/**
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

vector<int> lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> ans;
  for (int i = s; i < e; i++) {
    if (ans.empty() || f(ans.back(), i)) {
      ans.push_back(i);
    } else {
      *ranges::lower_bound(ans, i, f) = i;
    }
  }
  return ans;
}

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  ranges::sort(a); // O(n*log n)
  auto cmp = [&](int i, int j) { return a[i][1] > a[j][1]; };
  auto seq = lis(cmp, 0, n); // O(n*log n)
  int ans = seq.size();
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
