#include <stdio.h>

unsigned long lcg(unsigned long *seed);

unsigned long mlcg(unsigned long *seed);

double rand_double_sym_lcg(unsigned long *seed, double r);

double rand_double_sym_mlcg(unsigned long *seed, double r);