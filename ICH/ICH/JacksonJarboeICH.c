//Evan Jackson, William Jarboe
//ICH 10/31/2019
//This project will start with the num 191, and add
//i*111 to the sum, where i is the number of processes
//and will then print out that sum at process 0
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
    MPI_Status status;
    
    //Initialize MPI
    MPI_Init(NULL, NULL);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int sum = 191;
    
    //Loop through all iterations and send to next process the sum
    int i;
    for(i = 0; i < world_size-1; i++){
        if(world_rank == i){
            //sned sum to next process
            MPI_Send(&sum, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
            sum += (i+1)*111;
            MPI_Recv(&sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }
    }
    //for last thread, send back to 0
    if(world_rank == world_size - 1){
        sum += (i+1)*111;
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    //if 0, print out sum
    if(world_rank == 0){
        MPI_Recv(&sum, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, &status);
        printf("The sum of %i threads is %i\n", world_size, sum);
    }
    
    MPI_Finalize();
    
}

