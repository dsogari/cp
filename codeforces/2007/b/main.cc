/**
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
using Chr = Num<char>;

template <typename T> struct FenTreeMap {
  int n;
  unordered_map<int, T> nodes = {{0, {}}};
  FenTreeMap(int n) : n(n) {}
  T query(int i, auto &&f) const { // O(log n)
    assert(i < n);
    T ans = nodes.find(0)->second;
    for (i++; i > 0; i -= i & -i) {
      auto it = nodes.find(i);
      if (it != nodes.end()) {
        ans = f(ans, it->second);
      }
    }
    return ans;
  }
  void update(int i, auto &&f, const auto &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
};

const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };

struct Query {
  Chr type;
  Int l, r;
};

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  vector<Query> q(m);
  vector<i64> ans;
  FenTreeMap<i64> fen(1e9 + 1);
  for (int i = 0; i < n; i++) {
    fen.update(i64(a[i]), tmax, i64(a[i]));
  }
  for (auto &&[type, l, r] : q) {
    auto c = type == '+' ? 1 : -1;
    fen.update(l - 1, tmax, fen.query(l - 1, tmax) + c);
    fen.update(i64(r), tmax, fen.query(i64(r), tmax) - c);
    ans.push_back(fen.query(i64(n), tmax));
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
