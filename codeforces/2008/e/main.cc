/**
 * https://codeforces.com/contest/2008/submission/280787993
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

constexpr int lowerlatin = 'z' - 'a' + 1;

template <typename T, size_t N>
array<T, N> operator+(const array<T, N> &lhs, const array<T, N> &rhs) {
  array<T, N> ans;
  for (int i = 0; i < N; i++) {
    ans[i] = lhs[i] + rhs[i];
  }
  return ans;
}

void solve(int t) {
  Int n;
  Str s;
  int ans = n % 2;
  if (n > 2) {
    array<array<int, lowerlatin>, 2> pref = {}, suff = {};
    for (int i = 0; i < n; i++) {
      suff[i & 1][s[i] - 'a']++;
    }
    int mx = 0;
    if (ans) {
      for (int i = 0; i < n; i++) {
        suff[i & 1][s[i] - 'a']--;
        auto sumeven = pref[0] + suff[1];
        auto sumodd = pref[1] + suff[0];
        auto besteven = *ranges::max_element(sumeven);
        auto bestodd = *ranges::max_element(sumodd);
        mx = max(mx, besteven + bestodd);
        pref[i & 1][s[i] - 'a']++;
      }
    } else {
      auto besteven = *ranges::max_element(suff[0]);
      auto bestodd = *ranges::max_element(suff[1]);
      mx = besteven + bestodd;
    }
    ans += n - ans - mx;
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
