/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include <bits/stdc++.h>

using namespace std;

/**
 * Input number
 * LLDB initCommands:
 *  type summary add --summary-string "${var.x}" -x "^Number<"
 */
template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

/**
 * Input string
 * LLDB initCommands:
 *  type summary add --summary-string "${var._M_dataplus._M_p}" -x "^String<"
 */
template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

/**
 * Printing utilities
 */
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &a) {
  return os << a.first << ' ' << a.second;
}
template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T, size_t N>
ostream &operator<<(ostream &os, const span<T, N> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const list<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}

/**
 * Line output
 */
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }
