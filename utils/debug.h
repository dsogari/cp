/**
 * (c) 2024 Diego Sogari
 */
#include <cpp-dump.hpp>

/**
 * Pretty-prints variables
 * https://github.com/philip82148/cpp-dump
 */
#define debug cpp_dump

/**
 * Loads the input file
 */
#define init()                                                                 \
  auto _ =                                                                     \
      freopen(filesystem::path(__FILE__).replace_filename("input").c_str(),    \
              "r", stdin);
