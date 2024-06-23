#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
auto in = ifstream(filesystem::path(__FILE__).replace_filename("input.txt"));
auto &out = cout << fixed << setprecision(20);
#else
auto &in = (cin.tie(nullptr)->sync_with_stdio(false), cin);
auto &out = cout << fixed << setprecision(20);
#endif

void solve(int t)
{
  int n, k;
  in >> n >> k;
  set<int> nums;
  for (int i = 0, a; i < n; i++)
  {
    in >> a;
    if (nums.contains(a))
    {
      nums.erase(a);
    }
    else
    {
      nums.insert(a);
    }
  }
  list<int> nums2(nums.begin(), nums.end());
  int res = 0, bad = 0;
  for (auto it1 = nums2.begin(); nums2.size() > 1 && it1 != nums2.end();)
  {
    bool found = false;
    for (auto it2 = next(it1); !found && it2 != nums2.end(); it2++)
    {
      if ((*it2 - *it1) % k == 0)
      {
        nums2.erase(it2);
        res += (*it2 - *it1) / k;
        found = true;
      }
    }
    if (found)
    {
      it1 = nums2.erase(it1);
    }
    else if (bad++)
    {
      out << -1 << endl;
      return;
    }
  }
  out << res << endl;
}

int main()
{
  int t;
  in >> t;
  for (int i = 1; i <= t; ++i)
    solve(i);
}