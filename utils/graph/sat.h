/**
 * (c) 2024 Diego Sogari
 */
#include "scc.h"

/**
 * 2-Satisfiability solver
 */
struct TwoSat {
  const int n;
  Digraph g;
  TwoSat(int n) : g(2 * n), n(n) {}
  void add(int a, int b) { g.add(n + a, n + b); }
  void either(int a, int b) { implies(-a, b); }
  void notequal(int a, int b) { equal(-a, b); }
  void set(int a) { add(-a, a); }
  void equal(int a, int b) {
    implies(a, b);
    implies(-a, -b);
  }
  void implies(int a, int b) {
    add(a, b);   //  a ->  b
    add(-b, -a); // !b -> !a
  }
  bool operator()() const {
    SCC scc(g);
    for (int i = 1; i <= n; i++) {
      if (scc[n + i] == scc[n - i]) {
        return false;
      }
    }
    return true;
  }
};
