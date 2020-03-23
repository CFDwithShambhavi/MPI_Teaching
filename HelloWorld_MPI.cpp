#include <mpi.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv) ;
    
    // Number of processes
    int size ;
    MPI_Comm_size(MPI_COMM_WORLD, &size) ;
    
    // Rank of processes
    int rank ;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
    
    // Name of the processors
    char name[MPI_MAX_PROCESSOR_NAME] ;
    int length ;
    MPI_Get_processor_name(name, &length) ;
    
    // Print a hello world message
    printf("Hello world from processor %s, rank %d out of the %d processors\n", name, rank, size) ;
    
    // Finalize the MPI environment
    MPI_Finalize () ;
    
    return 0 ;
}
