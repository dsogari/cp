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

template <typename T> struct Str : basic_string<T> {
  using basic_string<T>::basic_string;
  Str() { cin >> *this; }
};
using String = Str<char>;

void solve(int t) {
  Int n;
  String s;
  if (n % 2 == 0) {
    return println("YES");
  }
  auto pref = s, suff = s;
  for (int i = 1, j = n - 2; i < n; i++, j--) { // O(n)
    pref[i] = min(pref[i], pref[i - 1]);
    suff[j] = min(suff[j], suff[j + 1]);
  }
  auto f = [&](int l, int r) {
    auto mxl = max(s[l], l % 2 == 0 || pref[l] < s[l] ? 'z' : 'y');
    auto mxr = max(s[r], r % 2 == 0 || suff[r] < s[r] ? 'z' : 'y');
    return max(s[l], s[r]) <= min(mxl, mxr);
  };
  for (int i = 1; i < n - 1; i++) { // O(n)
    if (s[i - 1] > s[i] && s[i] < s[i + 1]) {
      int l = i - 1, r = i + 1;
      for (; l > 0 && s[l - 1] > s[l]; l--)
        ; // find left boundary
      for (; r < n - 1 && s[r] < s[r + 1]; r++)
        ; // find right boundary
      if ((r - l + 1) % 2
              ? f(l, r) || (l + 1 < i && r - 1 > i && f(l + 1, r - 1))
              : (l + 1 < i && f(l + 1, r)) || (r - 1 > i && f(l, r - 1))) {
        return println("YES");
      }
      i = r;
    }
  }
  println("NO");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
