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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void solve(int t) {
  Int n, k;
  vector<array<Int, 2>> rect(n);
  for (auto &&[w, h] : rect) { // O(n)
    if (w > h) {
      swap(w, h);
    }
  }
  ranges::sort(rect); // O(n*log n)
  int ans = 0, pts = 0;
  auto f = [&](int w, int h) -> array<int, 2> { // O(1)
    auto c = min(w + h, k - pts);
    auto extra = w + h - c;
    auto side = min(w, extra / 2); // maximize the area to be cleared
    auto ops = w * h - side * (extra - side);
    return {c, ops};
  };
  vector<bool> vis(n);
  for (int i = 0; i < n && pts < k; i++) { // O(n^2)
    if (!vis[i]) {
      auto [w, h] = rect[i];
      auto [pts1, ops1] = f(w, h);
      int besti = i;
      for (int j = i + 1; j < n && rect[j][0] < h; j++) {
        if (!vis[j]) {
          auto [w2, h2] = rect[j];
          if (w2 * h2 < w * h) {
            auto [pts2, ops2] = f(w2, h2);
            if (pts2 * ops1 > ops2 * pts1) {
              pts1 = pts2;
              ops1 = ops2;
              besti = j;
            }
          }
        }
      }
      pts += pts1;
      ans += ops1;
      vis[besti] = true;
      if (besti > i) {
        i--;
      }
    }
  }
  println(pts >= k ? ans : -1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
