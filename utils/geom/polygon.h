/**
 * (c) 2024 Diego Sogari
 */
#include "point.h"

/**
 * Convex Hull
 */
template <typename T> struct Polygon : vector<Point<T>> {
  using vector<Point<T>>::vector;
};
