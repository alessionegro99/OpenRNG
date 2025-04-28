CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -pedantic -Wconversion -std=c99 -fopenmp
INCLUDES = -Iinclude

LIB_SOURCES = lib/random.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

SRC_SOURCES = src/pi.c src/pi_omp_naive.c
SRC_OBJECTS = $(SRC_SOURCES:.c=.o)

PI_OBJECTS = $(LIB_OBJECTS) src/pi.o
PI_OMP_NAIVE_OBJECTS = $(LIB_OBJECTS) src/pi_omp_naive.o
PI_OMP_OBJECTS = $(LIB_OBJECTS) src/pi_omp.o

TARGETS = pi pi_omp_naive pi_omp

all: $(TARGETS)

pi: $(PI_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

pi_omp_naive: $(PI_OMP_NAIVE_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

pi_omp: $(PI_OMP_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(LIB_OBJECTS) $(SRC_OBJECTS) $(TARGETS)

.PHONY: all clean
