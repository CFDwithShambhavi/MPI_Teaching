//
//  MPI_Send_Recieve2.cpp
//  
//
//  Created by Shambhavi Nandan on 3/24/20.
//

#include <mpi.h>
#include <iostream>

int main ()
{
    // Initialize MPI:
    MPI_Init (NULL, NULL) ;
    
    // Get the number of processors:
    int count ;
    MPI_Comm_size (MPI_COMM_WORLD, &count) ;
    
    // Get the rank of the current processor:
    int rank ;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank) ;
    
    // Get the current processor name:
    char name[MPI_MAX_PROCESSOR_NAME] ;
    int len ;
    MPI_Get_processor_name (name, &len) ;
    
    std::cout <<std::endl ;
    
    if (rank == 0) // Processor 0
    {
        int send_data[] = {1, 2, 3, 4, 5} ;
        int count = sizeof(send_data)/sizeof(int) ;
        int* p = send_data ;
        int recieving_Processor_rank = 1 ;
        
        // Send data to processor 1:
        MPI_Send (p, count, MPI_INT, recieving_Processor_rank, 0,                     MPI_COMM_WORLD) ;
        
        std::cout <<"Hello this is processor " <<rank <<std::endl ;
        std::cout <<"Following data is sent to processor: " <<recieving_Processor_rank <<std::endl ;
        std::cout <<"...................................." <<std::endl ;
        for (int i = 0; i < count; i++)
        {
            std::cout <<send_data[i] <<std::endl ;
        }
        std::cout <<"...................................." <<std::endl ;
    }
    
    else if (rank == 1) // Processor 1
    {
        MPI_Status status ;
        int sending_Processor_rank = 0;
        int count ;
        
        // Get informations about the data recieved from processor 0:
        MPI_Probe (0, 0, MPI_COMM_WORLD, &status) ;
        
        MPI_Get_count (&status, MPI_INT, &count) ;
        
        int recv_data[count] ;
        int* p = recv_data ;
        
        // Recieving data to processor 0:
        MPI_Recv (p, count, MPI_INT, sending_Processor_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        
        std::cout <<"Hello this is processor " <<rank <<std::endl ;
        std::cout <<"Following data is recieved from processor: " <<sending_Processor_rank <<std::endl ;
        std::cout <<"...................................." <<std::endl ;
        for (int i = 0; i < count; i++)
        {
            std::cout <<recv_data[i] <<std::endl ;
        }
        std::cout <<"...................................." <<std::endl ;
        
    }
    
    MPI_Finalize () ;
}
