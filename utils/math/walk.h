/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Inclusion Walk
 */
void inclusion(int n, int m, int w, int h, auto &&f) {
  int rmx = min(h, n - h + 1); // window size vs number of windows
  int cmx = min(w, m - w + 1); // idem for columns
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int rc = min({rmx, i + 1, n - i}); // number of inclusions
      int cc = min({cmx, j + 1, m - j}); // idem for columns
      f(i, j, rc * cc);
    }
  }
}

/**
 * Spiral Walk
 * @see https://stackoverflow.com/a/33639875/4725347
 */
void spiral(auto &&f) {
  for (int x = 0, y = 0, d = 1, m = 1; true; d = -d, m++) {
    for (; 2 * x * d < m; x += d) {
      if (!f(x, y)) {
        return;
      }
    }
    for (; 2 * y * d < m; y += d) {
      if (!f(x, y)) {
        return;
      }
    }
  }
}
