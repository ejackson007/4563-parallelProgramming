#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[])
{
   int myid, numprocs; 
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
   MPI_Comm_rank (MPI_COMM_WORLD,&myid); 
   
   if (myid == 0)   
      printf("Hello slaves, my old friends! I am your master Process #%d\n",myid);
   else
      printf("Hello from your humble servant, process #%d\n", myid);
   /* CALL MPI_Finalize() TO CLEAN UP PROCESSES               */
MPI_Finalize();
}