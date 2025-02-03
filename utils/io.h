/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Input number
 * LLDB: type summary add --summary-string "${var.x}" -x "^Num<"
 */
template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

/**
 * Input string
 * LLDB: type summary add --summary-string "${var._M_dataplus._M_p}" -x "^Str<"
 */
template <typename T> struct Str : basic_string<T> {
  using basic_string<T>::basic_string;
  Str() { cin >> *this; }
};

/**
 * Common input types
 */
using Int = Num<int>;
using Chr = Num<char>;
using I64 = Num<i64>;
using U64 = Num<u64>;
using F64 = Num<double>;
using String = Str<char>;

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
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }
