/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Common constants
 */
constexpr int lowerlatin = 'z' - 'a' + 1;
constexpr int upperlatin = 'Z' - 'A' + 1;
const string vowels = "aeiou";

/**
 * ASCII character histogram
 */
struct AsciiHist : array<int, CHAR_MAX + 1> {
  AsciiHist(const string &s) : array{} {
    for (auto &&c : s) {
      (*this)[c]++;
    }
  }
};
