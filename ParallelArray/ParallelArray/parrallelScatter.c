#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>

#define SIZE 640000

// Fills array
float *create_all_nums(int num_elements) {
    float *all_nums = (float *)malloc(sizeof(float) * num_elements);
    assert(all_nums != NULL);
    int i;
    for (i = 0; i < num_elements; i++) {
        all_nums[i] = i + 1;
    }
    return all_nums;
}

// Computes the sum of an array of numbers
float compute_sum(float *array, int num_elements) {
    float sum = 0.f;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum;
}

int main(int argc, char** argv) {
    
    MPI_Init(NULL, NULL);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int num_elements_per_proc = SIZE / world_size;
    
    // Create a random array of elements on the root process. Its total
    // size will be the number of elements per process times the number
    // of processes
    float *all_nums = NULL;
    if (world_rank == 0) {
        all_nums = create_all_nums(num_elements_per_proc * world_size);
    }
    
    // For each process, create a buffer that will hold a subset of the entire
    // array
    float *sub_all_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);
    assert(sub_all_nums != NULL);
    
    // Scatter the array from the root process to all processes in
    // the MPI world
    MPI_Scatter(all_nums, num_elements_per_proc, MPI_FLOAT, sub_all_nums,
                num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    // Compute the sum of subset
    float buffer_sum = compute_sum(sub_all_nums, num_elements_per_proc);
    
    //Sum each value
    float sum;
    MPI_Reduce(&buffer_sum, &sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Print and cleanup
    if (world_rank == 0) {
        printf("Sum of all elements is %ld\n", (long int)sum);
        free(all_nums);
    }
    free(sub_all_nums);
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
