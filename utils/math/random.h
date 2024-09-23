/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Seed Sequence for use with PRNGs
 */
seed_seq seq{(u64)now().time_since_epoch().count(),
             (u64)make_unique<char>().get(), (u64)random_device{}()};

/**
 * Mersenne Twister pseudo-random number generator
 */
mt19937 rng(seq);
mt19937_64 rng64(seq);

/**
 * Uniform Distribution
 */
using Uniform = uniform_int_distribution<int>;
