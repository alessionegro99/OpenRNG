#include "../include/macro.h"

#include "../include/random.h"

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stdout, "How to use:\n");
    fprintf(stdout, "  %s n_trials seed:\n", argv[0]);
    fprintf(stdout, "  n_trials = number of points used to estimate PI\n");
    fprintf(stdout, "  seed = starting seed for Random Number Generation\n");
    return EXIT_SUCCESS;
  }

  if ((atol(argv[1]) <= 0) || (atol(argv[2]) < 0)) {
    fprintf(stderr,
            "n_trials must be strictly positive, seed must be positive!\n");
    return EXIT_FAILURE;
  }

  long i, N_circ, n_trials;
  unsigned long seed;
  double pi, x, y, r, err, elapsed;

  struct timespec start, end;

  n_trials = atol(argv[1]);
  seed = (unsigned long)atol(argv[2]);

  N_circ = 0;

  r = 1.0; // radius of circle. Side of square is 2*r

  // task 2: use mersenne twister for a proper evaluation
  clock_gettime(CLOCK_MONOTONIC, &start);

#pragma omp parallel for num_threads(NTHREADS) private(x, y, seed) reduction(+ : N_circ)
  for (i = 0; i < n_trials; i++) {
    x = rand_double_sym_mlcg(&seed, r); // uniform mlcg in [-r,r]
    y = rand_double_sym_mlcg(&seed, r);
    if (x * x + y * y <= r * r)
      N_circ += 1;
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  elapsed = (double)(end.tv_sec - start.tv_sec) +
            (double)(end.tv_nsec - start.tv_nsec) / 1e9;

  pi = 4.0 * ((double)N_circ / (double)n_trials);
  err = fabs(1 - pi / PI);

  printf("Using %d threads\n", NTHREADS);
  printf("trials pi error time\n");
  printf("%ld %.12f %.12f %f\n", n_trials, pi, err, elapsed);

  return EXIT_SUCCESS;
}
