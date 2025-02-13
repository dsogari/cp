/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

using namespace std;
using i64 = int64_t;

constexpr int maxt = 250, maxn = 18, maxa = 1e9;

inline vector<vector<int>> getShelves(InStream &in, int n) {
  auto k = in.readInt(1, n, "number of shelves");
  if (!in.seekEoln()) {
    in.quit(_pe, "Expected EOLN");
  }
  vector<vector<int>> shelves(k);
  for (int i = 0; i < n; i++) {
    auto j = in.readInt(1, k, "shelf number");
    shelves[j - 1].push_back(i);
  }
  if (!in.seekEoln()) {
    in.quit(_pe, "Expected EOLN");
  }
  for (int j = 0; j < k; j++) {
    if (shelves[j].empty()) {
      in.quitf(_wa, "shelf %d has no books", j + 1);
    }
  }
  return shelves;
}

inline array<int, 2> checkAns(InStream &in, const vector<array<int, 2>> &a) {
  auto cmp = [&](int i, int j) { return a[i][0] < a[j][0]; };
  auto shelves = getShelves(in, a.size());
  int result = 0, k = shelves.size();
  for (int j = 0; j < k; j++) {
    auto &shelf = shelves[j];
    int len = shelf.size();
    ranges::sort(shelf, cmp);
    for (int i = 1; i < len; i++) {
      if (a[shelf[i - 1]][1] > a[shelf[i]][1]) {
        in.quitf(_wa, "shelf %d does not conform to constraints", j + 1);
      }
    }
    result = max(result, len);
  }
  return {k, result};
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(1, maxn, "n");
    vector<array<int, 2>> a(n);
    for (int j = 0; j < n; j++) {
      a[j][0] = inf.readInt(1, maxa, "w");
      a[j][1] = inf.readInt(1, maxa, "h");
    }
    auto [kpans, lpans] = checkAns(ouf, a);
    auto [kjans, ljans] = checkAns(ans, a);
    if (kpans != kjans) {
      quitf(_wa, "k: participant=%d, jury=%d", kpans, kjans);
    } else if (lpans > ljans) {
      quitf(_wa, "len: participant=%d, jury=%d", lpans, ljans);
    } else if (lpans < ljans) {
      quitf(_fail, "len: participant=%d, jury=%d", lpans, ljans);
    }
  }
  quit(_ok, "");
}
