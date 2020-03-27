//
//  MPI_GoesAround_ComesAround.cpp
//  
//
//  Created by Shambhavi Nandan on 3/27/20.
//

#include <mpi.h>
#include <iostream>

int main ()
{
    // Initialize MPI:
    MPI_Init (NULL, NULL) ;
    
    // Get the rank of the processor in the communicator:
    int processor_rank ;
    MPI_Comm_rank (MPI_COMM_WORLD, &processor_rank) ;
    
    // Gat the size of the communicator: gives the number of processors
    int size ;
    MPI_Comm_size (MPI_COMM_WORLD, &size) ;
    
    // Get the name of the processor:
    char processor_name[MPI_MAX_PROCESSOR_NAME] ;
    int name_len ;
    MPI_Get_processor_name (processor_name, &name_len) ;
    
    int message ;
    
    if (processor_rank != 0)
    {
        MPI_Recv (&message, 1, MPI_INT, processor_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        
        std::cout <<"Processor " <<processor_rank <<" recieved " <<message <<" from " <<(processor_rank - 1) <<std::endl ;
    }
    
    else
    {
        message = 1011 ;
    }
    
    MPI_Send (&message, 1, MPI_INT, (processor_rank + 1) % size, 0, MPI_COMM_WORLD) ;
    
    if (processor_rank == 0)
    {
        
        MPI_Recv (&message, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        
        std::cout <<"Processor " <<processor_rank <<" recieved " <<message <<" from " <<(size - 1) <<std::endl ;
    }
    
    MPI_Finalize () ;
}
