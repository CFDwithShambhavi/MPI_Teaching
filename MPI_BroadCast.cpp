//
//  MPI_BroadCast.cpp
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
    
    // Get the number of processors in a communicator:
    int processor_size ;
    MPI_Comm_size (MPI_COMM_WORLD, &processor_size) ;
    
    // Get the rank of current processor in a communicator:
    int rank ;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank) ;
    
    // Get the name of the current processor in a communicator:
    char name[MPI_MAX_PROCESSOR_NAME] ;
    int len ;
    MPI_Get_processor_name (name, &len) ;
    
    // MPI Broadcast demonstration for 3 processors:
    if (processor_size < 3)
    {
        std::cout <<"Currently there are " <<processor_size <<" processors"               <<std::endl ;
        std::cout <<"The current program requires exactly 3 processors" <<std::endl ;
        MPI_Abort (MPI_COMM_WORLD, 1) ;
    }
    // Initialize root processor rank:
    int root_processor_rank = 0 ;
    
    if (rank == root_processor_rank)
    {
        // Broadcast data to processor 1 & 2:
        int data = 100 ;
        int count = 1 ;
        /*
        MPI_Bcast (void* data, int count, MPI_Datatype datatype,
                   int root, MPI_Comm communicator)
        */
        
        MPI_Bcast (&data, count, MPI_INT, root_processor_rank, MPI_COMM_WORLD) ;
        
        std::cout <<"Root Processor " <<rank <<" send " <<data <<" to processors 0 & 1" <<std::endl ;
    }
    
    else if (rank == 1)
    {
        int data ;
        int count = 1 ;
        MPI_Bcast (&data, count, MPI_INT, root_processor_rank, MPI_COMM_WORLD) ;
        
        std::cout <<"Processor " <<rank <<" recieved " <<data <<" from processor "           <<root_processor_rank <<std::endl ;
    }
    
    else if (rank == 2)
    {
        int data ;
        int count = 1 ;
        MPI_Bcast (&data, count, MPI_INT, root_processor_rank, MPI_COMM_WORLD) ;
        
        std::cout <<"Processor " <<rank <<" recieved " <<data <<" from processor "           <<root_processor_rank <<std::endl ;
    }
    
    MPI_Finalize () ;
}
