#include "../include/random.h"

unsigned long lcg(unsigned long *seed) {
  const unsigned long a = 1664525;
  const unsigned long c = 1013904223;
  const unsigned long m = 1UL << 32;

  *seed = (a * (*seed) + c) % m;
  return *seed;
}

unsigned long mlcg(unsigned long *seed) {
  const unsigned long a = 16807;
  const unsigned long m = 2147483647;

  *seed = (a * (*seed)) % m;
  return *seed;
}

double rand_double_sym_lcg(unsigned long *seed, double r) {
  unsigned long val = lcg(seed);
  double norm = (double)val / (double)(1UL << 32);
  return -r + (2.0 * r * norm);
}

double rand_double_sym_mlcg(unsigned long *seed, double r) {
  const unsigned long m = 2147483647;

  unsigned long val = mlcg(seed);
  double norm = (double)val / (double)m;
  return -r + (2.0 * r * norm);
}