/**
 * https://codeforces.com/contest/2003/submission/278166151
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

constexpr int mxa = 1e9;

void solve(int t) { // O(sum(li))
  Int n, m;
  vector<vector<Int>> a(n);
  int best = 0;
  for (auto &ai : a) { // O(sum(li))
    Int li;
    ai.resize(li);
    vector<bool> vis(li + 2);
    for (auto &&aai : ai) { // O(li)
      if (aai < li + 2) {
        vis[aai] = true;
      }
    }
    for (int i = 0, c = 0; i < li + 2 && c < 2; i++) { // O(li)
      if (!vis[i] && c++) {
        best = max(best, i);
      }
    }
  }
  auto [lt, gt] = m < best ? array<i64, 2>{m, best} : array<i64, 2>{best, m};
  i64 ans = (lt + 1) * best + (gt - best) * (best + m + 1) / 2;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
