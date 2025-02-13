/**
 * (c) 2025 Diego Sogari
 */
#include "testlib.h"

using namespace std;
using i64 = int64_t;

constexpr int maxt = 1e3, maxn = 5e3, maxa = 1e9, maxh = 1e9;

inline vector<int> getPath(InStream &in, int n) {
  vector<int> path;
  vector<bool> used(n + 1);
  auto add = [&](int i) {
    if (used[i]) {
      in.quitf(_wa, "tree %d was used twice", i);
    }
    path.push_back(i);
    used[i] = true;
  };
  add(1); // path starts at Tarzan's tree
  auto len = in.readInt(0, n - 1, "number of moves");
  if (!in.seekEoln()) {
    in.quit(_pe, "Expected EOLN");
  }
  if (len == 0) {
    return path;
  }
  for (int i = 1; i <= len; i++) {
    auto j = in.readInt(1, n, format("path[%d]", i));
    add(j);
  }
  if (!in.seekEoln()) {
    in.quit(_pe, "Expected EOLN");
  }
  if (path.back() != n) {
    in.quitf(_wa, "path doesn't end in Ape's tree: expected %d, found %d", n,
             path.back());
  }
  return path;
}

inline double readAndCheckAnswer(InStream &in, const vector<array<int, 3>> &a) {
  auto path = getPath(in, a.size());
  double result = 0;
  for (int i = 1; i < path.size(); i++) {
    auto j = path[i - 1], k = path[i];
    auto [xj, yj, hj] = a[j - 1];
    auto [xk, yk, hk] = a[k - 1];
    auto dx = abs(xk - xj), dy = abs(yk - yj);
    auto d = sqrt(i64(dx) * dx + i64(dy) * dy);
    if (d > hj) {
      in.quitf(_wa, "tree %d cannot be reached from tree %d", k, j);
    }
    result += d;
  }
  return result;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto n = inf.readInt(2, maxn, "n");
    set<array<int, 2>> used;
    vector<array<int, 3>> a(n);
    for (int j = 0; j < n; j++) {
      auto &[x, y, h] = a[j];
      x = inf.readInt(-maxa, maxa, "x");
      y = inf.readInt(-maxa, maxa, "y");
      h = inf.readInt(1, maxh, "h");
      if (!used.insert({x, y}).second) {
        quitf(_fail, "duplicate tree at location (%d,%d)", x, y);
      }
    }
    auto pans = readAndCheckAnswer(ouf, a);
    auto jans = readAndCheckAnswer(ans, a);
    if ((pans == 0 && jans > 0) || pans > jans + ValidatorBoundsHit::EPS) {
      quitf(_wa, "participant=%f, jury=%f", pans, jans);
    } else if (pans < jans - ValidatorBoundsHit::EPS) {
      quitf(_fail, "participant=%f, jury=%f", pans, jans);
    }
  }
  quit(_ok, "");
}
