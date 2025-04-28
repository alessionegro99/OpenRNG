module load GCC
g++ -O3 -fopenmp -mavx2 -mfma -mtune=znver2 -march=znver2 stream.cpp -o stream
