#include <immintrin.h>
#include <iostream>
#include <omp.h>

int main()
{
    double start = omp_get_wtime();
    std::cout << "Hello HPC" << std::endl;
    double end = omp_get_wtime();
    std::cout << "execution time: " << end - start << std::endl;
    return (0);
}
