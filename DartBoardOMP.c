#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>

double EstimatePi(int total_throws) {
    int hits_count = 0;
    unsigned int seed = (unsigned int)time(NULL);

    #pragma omp parallel reduction(+:hits_count)
    {
        unsigned int thread_seed = seed + omp_get_thread_num(); // Unique seed per thread
        int local_hits = 0;

        #pragma omp for
        for (int k = 0; k < total_throws; k++) {
            double x_axis = (double)rand_r(&thread_seed) / RAND_MAX;
            double y_axis = (double)rand_r(&thread_seed) / RAND_MAX;

            if (x_axis * x_axis + y_axis * y_axis < 1.0) {
                hits_count++;
            }
        }
    }

    double Pi_aprox = 4.0 * hits_count / (double)(total_throws);
    return Pi_aprox;
}

int main(int argc, char *argv[]){
    struct timespec start, end;
    double elapsed_time;
    int total_throws, hits;
    const double factor = 1.0 / RAND_MAX;
    total_throws = atoi(argv[1]);
    int verbose = 0;

    if (argc > 2 && strcmp(argv[2], "-v") == 0) {//comando verbose
        verbose = 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &start); //Inicia Captura del tiempo

    //initializa el generador de numeros aleatorios
    srand((unsigned)time(NULL));

    // Initializa OMP_NUM_THREADS 
    int OMP_NUM_THREADS = omp_get_max_threads();

    // Dedica el numero de hilos con base en la entrada
    omp_set_num_threads(OMP_NUM_THREADS);

    //Calcula el pi aproximado
    double pi_aprox = EstimatePi(total_throws);

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    if(verbose){
        printf("Pi aprox: %lf\n", pi_aprox);
    }

    printf(" %f\n", elapsed_time);

    return 0;
}