/**
 * https://codeforces.com/contest/1971/submission/267631206
 *
 * Copyright (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;
using MinHeap = priority_queue<int, vector<int>, greater<int>>;

void solve(int t) {
  int n;
  cin >> n;
  vector<int> a(n);
  map<int, MinHeap> groups;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    groups[a[i] >> 2].push(a[i]);
  }
  for (int i = 0; i < n; i++) {
    auto &heap = groups[a[i] >> 2];
    cout << heap.top() << ' ';
    heap.pop();
  }
  cout << endl;
}

int main() {
#ifdef LOCAL
  freopen(path(__FILE__).replace_filename("input.txt").c_str(), "r", stdin);
#endif
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve(i);
  }
}