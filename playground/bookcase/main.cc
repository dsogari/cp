/**
 * Bookcase
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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
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

int binsearch(auto &&f, int s, int e) { // (s, e] O(log n)
  while (s < e) {
    auto m = (s + e + 1) / 2;
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
}

int lis(auto &&f, int s, int e) { // [s, e) O(n*log n)
  vector<int> inc = {s};
  for (int i = s + 1; i < e; i++) {
    if (f(inc.back(), i)) {
      inc.push_back(i);
    } else {
      *ranges::lower_bound(inc, i, f) = i;
    }
  }
  return inc.size() - (s >= e);
}

int len1(auto &&b, int n, int k) {
  vector<int> s(k, -1), c(k);
  auto lte = [&](int i, int j) {
    return b[i][0] <= b[j][0] && b[i][1] <= b[j][1];
  };
  int ans = n;
  auto f = [&](auto &self, int i) -> void {
    if (i == n) {
      ans = min(ans, *ranges::max_element(c));
      return;
    }
    for (int j = 0; j < k; j++) {
      if (s[j] < 0 || lte(s[j], i)) {
        auto saved = s[j];
        s[j] = i, c[j]++;
        self(self, i + 1);
        s[j] = saved, c[j]--; // backtrack
      }
    }
  };
  f(f, 0);
  return ans;
}

int len2(auto &&b, int n, int k) {
  auto f = [&](int l) {
    vector<vector<int>> heights = {{INT_MAX}};
    auto cmp = [&](auto &v1, auto &v2) { return v1.back() > v2.back(); };
    vector<int> toupdate;
    int ans = 0;
    auto f2 = [&]() {
      int tocut = 0;
      for (auto i : toupdate) {
        heights[i].resize(heights[i].size() - l);
        if (heights[i].empty()) {
          heights[i].push_back(0);
          tocut++;
        }
      }
      ranges::sort(heights, cmp);
      if (tocut) {
        heights.resize(heights.size() - tocut);
      }
      toupdate.clear();
    };
    int prev = 0;
    for (auto &[w, h] : b) {
      if (w > prev) {
        if (toupdate.size()) {
          f2();
        }
        prev = w;
      }
      if (heights.back().back() > h) {
        heights.push_back({h});
      } else {
        auto it = ranges::lower_bound(heights, vector<int>{h}, cmp);
        it->push_back(h);
        if (it->size() == l) {
          toupdate.push_back(it - heights.begin());
          ans++;
        }
      }
    }
    if (toupdate.size()) {
      f2();
    }
    ans += heights.size() - 1;
    return ans > k;
  };
  return binsearch(f, n / k, n - k + 1) + 1;
}

void solve(int t) {
  // Int n;
  // vector<array<Int, 2>> b(n);
  int n = 12;
  vector<array<int, 2>> b(n);
  for (auto &&bi : b) {
    bi[0] = rand() % n + 1;
    bi[1] = rand() % n + 1;
  }
  ranges::sort(b); // O(n*log n)
  auto cmp = [&](int i, int j) { return b[i][1] > b[j][1]; };
  int k = lis(cmp, 0, n); // O(n*log n)
  int l1 = len1(b, n, k);
  int l2 = len2(b, n, k);
  // assert(l1 == l2);
  println(b, k, l1, l2);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
