//**************************************************************

// Assignment #2

// Name: Evan Jackson, William Jarboe

// Parallel Programming Date: Date of Submission (10/31/2019)

//***************************************************************

// This program was made to run the Cooley-Tukey FFT algorithm in parallel
// this is done recursively by splitting up the initial array into multiple parts,
// and each part follows the general recursion for the FFT transformation. The cdOutput shows
// each value for the real and the imaginary
//
// TO RUN IN TURING:
// qsub fftscatter<16 or 32>
//
// TO RUN IN STAMPEDE:
// mpicc fftscatter<process #>.exe -o JacksonJarboeParVer1024.c
// sbatch fftscatter<process #>.exe

//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 1024

double PI = 22/7;
typedef double complex cplx;

//fillArray(num_elements)
//this creates an array of double complex and returns
//them. It fills the array with the values at the top
//and then fills the remaining with 0s. returns the array
//created
cplx *fillArray(num_elements){
    cplx *all_nums = (cplx *)malloc(sizeof(cplx) * num_elements);
    assert(all_nums != NULL);
    all_nums[0] = 3.6 + 2.6*I;
    all_nums[1] = 2.9 + 6.3*I;
    all_nums[2] = 5.6 + 4*I;
    all_nums[3] = 4.8 + 9.1*I;
    all_nums[4] = 3.3 + 0.4*I;
    all_nums[5] = 5.9 + 4.8*I;
    all_nums[6] = 5 + 2.6*I;
    all_nums[7] = 4.3 + 4.1*I;
    for(int i = 8; i < num_elements; i++)
        all_nums[i] = 0;
    return all_nums;
}

//recursiveFFT(cdBuf, cdOut, n, iteration)
//This is the recursive part of the array. Since you need to
//compare each spot after it has "changed" an cdOut array is made to
//keep the original version. The changes to the array is
//made to the cdBuffer array, needing no return in the recursive part
//of the function.
void recursiveFFT(cplx * cdBuf, cplx * cdOut, int n, int iteration)
{
    if (iteration < n) {
        recursiveFFT(cdOut, cdBuf, n, iteration * 2);
        recursiveFFT(cdOut + iteration, cdBuf + iteration, n, iteration * 2);
        
        for (int i = 0; i < n; i += 2 * iteration) {
            double complex cdExponent = cexp(-I * PI * i / n) * cdOut[i + iteration];
            cdBuf[i / 2]     = cdOut[i] + cdExponent;
            cdBuf[(i + n)/2] = cdOut[i] - cdExponent;
        }
    }
}

//FastFourierTransform(cdBuf, n)
//This function takes in the array of complex doubles you want to perform FFT on
//and creates a copy needed for the recursion, and then passes
//both into the recursive function. Returns array that has calculated values
cplx* FastFourierTransform(cplx * cdBuf, int n)
{
    cplx *cdOut = (cplx *)malloc(sizeof(cplx) * n);
    assert(cdOut != NULL);
    
    for (int i = 0; i < n; i++)
        cdOut[i] = cdBuf[i];
    
    recursiveFFT(cdBuf, cdOut, n, 1);
    return cdBuf;
}

//main()
//Function carries out all the main function for the program
//It creates the MPI world, and then dictates the scattering of the array
//returns 0.
int main()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    MPI_Init(NULL, NULL);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int num_elements_per_proc = SIZE / world_size;
    
    //create array with all values
    cplx *cdBuf = NULL;
    if (world_rank == 0){
        cdBuf = fillArray(SIZE);
    }
    
    // For each process, create a cdBuffer that will hold a subset of the entire
    // array
    cplx *sub_cplx = (cplx *)malloc(sizeof(cplx) * num_elements_per_proc);
    assert(sub_cplx != NULL);
    
    //Scatter all values into smaller arrays.
    MPI_Scatter(cdBuf, num_elements_per_proc, MPI_C_COMPLEX, sub_cplx, num_elements_per_proc, MPI_C_COMPLEX, 0, MPI_COMM_WORLD);
    
    //do fft for each sub, and put it in a partial to be gathered
    cplx* partial = FastFourierTransform(sub_cplx, num_elements_per_proc);
    
    //Gather all processes back to root
    cplx * completed = NULL;
    if(world_rank == 0)
        completed = malloc(sizeof(cplx) * SIZE);
    
    MPI_Gather(partial, num_elements_per_proc, MPI_C_COMPLEX, completed, num_elements_per_proc, MPI_C_COMPLEX, 0, MPI_COMM_WORLD);
    
    //ensure all values are gathered before printing
    MPI_Barrier(MPI_COMM_WORLD);
    
    //root process prints values
    if(world_rank == 0){
        printf("TOTAL PROCESSED SAMPLES: %d\n", SIZE);
        printf("=====================================\n");
        for(int i=0; i < SIZE; i++){
            //print real and imaginary values
            printf("XR[%d]: %f  XI[%d]: %f\n", i, creal(completed[i]), i, cimag(completed[i]));
            printf("=====================================\n");
        }
    }
    
    //end the MPI process
    MPI_Finalize();
    gettimeofday(&end, NULL);
    printf("%ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    
    return 0;
}

