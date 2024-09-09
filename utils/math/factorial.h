/**
 * (c) 2024 Diego Sogari
 */
#include "mod.h"

/**
 * (Modular) Factorial
 */
template <typename T> struct Fac : vector<Mod<T>> {
  Fac() : vector<Mod<T>>(1, 1) {}
  Mod<T> operator[](int n) {
    while (this->size() <= n) {
      this->push_back(this->back() * this->size());
    }
    return vector<Mod<T>>::operator[](n);
  }
};
