/**
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

struct Str : string {
  Str() { cin >> *this; }
};

struct Manacher : vector<int> {
  Manacher(auto &&a, int s = 0) : Manacher(a, s, a.size()) {}
  Manacher(auto &&a, int s, int e) : vector<int>(e - s) { // [s, e) O(n)
    auto &z = *this;
    for (int i = 0, j = 0; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[max(0, 2 * j - i)]));
      while (i + c + s < e && i - c >= s && a[i + c + s] == a[i - c + s]) {
        c++, j = i; // update center of palindrome
      }
    }
  }
};

vector<array<int, 2>> manacher(auto &&a, int s, int e, auto d) { // [s, e) O(n)
  typename remove_cvref<decltype(a)>::type b = {d};
  for (int i = s; i < e; i++) {
    b.insert(b.end(), {a[i], d});
  }
  Manacher z(b);
  vector<array<int, 2>> ans(e - s);
  for (int i = 0; i < e - s; i++) {
    ans[i][0] = (z[2 * i] - 1) / 2; // even
    ans[i][1] = (z[2 * i + 1]) / 2; // odd
  }
  return ans;
}

void solve(int t) {
  Int n;
  Str s;
  auto a = manacher(static_cast<string>(s), 0, n, '#'); // O(n)
  vector<int> b(n + 1);
  for (auto &&[even, odd] : a) { // O(n)
    b[even * 2]++;
    b[odd * 2 - 1]++;
  }
  for (int i = n - 2; i > 0; i--) { // O(n)
    b[i] += b[i + 2];
  }
  vector<double> ans(n);
  for (int i = 0; i < n; i++) { // O(n)
    ans[i] = b[i + 1] / double(n - i);
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
