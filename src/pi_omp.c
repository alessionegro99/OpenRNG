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

  long i, N_circ, n_trials, tid;
  unsigned long seed[NTHREADS];
  double pi, x, y, r, err, elapsed;

  struct timespec start, end;

  n_trials = atol(argv[1]);
  seed[0] = (unsigned long)atol(argv[2]);

  for (i = 1; i < NTHREADS; i++) {
    seed[i] = seed[0] + (unsigned int)i;
  }

  N_circ = 0;

  r = 1.0; // radius of circle. Side of square is 2*r

  // add parallel init for seed thread dependent
  // create a thread dependent thread local seed variable

  // task 2: use mersenne twister for a proper evaluation
  clock_gettime(CLOCK_MONOTONIC, &start);

#pragma omp parallel num_threads(NTHREADS) private(x, y, tid)
  {
    
    tid = omp_get_thread_num();
#pragma omp for reduction(+ : N_circ)
    for (i = 0; i < n_trials; i++) {
      x = rand_double_sym_mlcg(&seed[tid], r);
      y = rand_double_sym_mlcg(&seed[tid], r);
      if (x * x + y * y <= r * r)
        N_circ += 1;
    }
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
