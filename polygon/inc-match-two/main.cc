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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

const greater<char> gt;

void solve(int t) {
  Str s;
  if (s.size() % 2) {
    auto it = ranges::max_element(s);
    if ((is_sorted(s.begin(), it) && is_sorted(next(it), s.end(), gt)) ||
        (*it == 'z' && (it - s.begin()) % 2 && is_sorted(s.begin(), it, gt) &&
         is_sorted(next(it), s.end()))) {
      return println("NO"); // either there are no valleys or there is a single
                            // peak with value 'z' that cannot be matched
    }
  }
  println("YES"); // either the length is even or there is a valley of odd
                  // length that can be removed
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
