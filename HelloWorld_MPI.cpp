#include <mpi.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv) ;
    
    // Number of processes
    int world_size ;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size) ;
    
    // Rank of processes
    int world_rank ;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank) ;
    
    // Name of the processors
    char processor_name[MPI_MAX_PROCESSOR_NAME] ;
    int name_len ;
    MPI_Get_processor_name(processor_name, &name_len) ;
    
    // Print a hello world message
    printf("Hello world from processor %s, rank %d out of the %d processors\n", processor_name, world_rank, world_size) ;
    
    // Finalize the MPI environment
    MPI_Finalize () ;
    
    return 0 ;
}
