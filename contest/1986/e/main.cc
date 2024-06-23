#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;

void solve(int t) {
  int n, k;
  cin >> n >> k;
  set<int> nums;
  for (int i = 0, a; i < n; i++) {
    cin >> a;
    if (nums.contains(a)) {
      nums.erase(a);
    } else {
      nums.insert(a);
    }
  }
  list<int> nums2(nums.begin(), nums.end());
  int res = 0, bad = 0;
  for (auto it1 = nums2.begin(); nums2.size() > 1 && it1 != nums2.end();) {
    bool found = false;
    for (auto it2 = next(it1); !found && it2 != nums2.end(); it2++) {
      if ((*it2 - *it1) % k == 0) {
        nums2.erase(it2);
        res += (*it2 - *it1) / k;
        found = true;
      }
    }
    if (found) {
      it1 = nums2.erase(it1);
    } else if (bad++) {
      cout << -1 << endl;
      return;
    }
  }
  cout << res << endl;
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