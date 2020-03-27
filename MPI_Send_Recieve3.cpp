//
//  MPI_Send_Recieve3.cpp
//  
//
//  Created by Shambhavi Nandan on 3/27/20.
//

#include <mpi.h>
#include <iostream>

int main()
{
    // Initialize MPI environment:
    MPI_Init (NULL, NULL) ;
    
    // Get the rank of the processor in the communicator:
    int rank ;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank) ;
    
    // Gat the size of the communicator: gives the number of processors
    int size ;
    MPI_Comm_size (MPI_COMM_WORLD, &size) ;
    
    // Get the name of the processor:
    char processor_name[MPI_MAX_PROCESSOR_NAME] ;
    int name_len ;
    MPI_Get_processor_name (processor_name, &name_len) ;
    
    // This program needs 3-processors:
    if (size < 3 || size > 3)
    {
        std::cout <<"Currently there are " <<size <<" processors" <<std::endl ;
        std::cout <<"The current program requires exactly 3 processors" <<std::endl ;
        MPI_Abort (MPI_COMM_WORLD, 1) ;
    }
    
    // Send and Recieve functionality :
    
    if (rank == 0) // Processor 0
    {
        int data = 10 ;
        int recieving_Processor_rank = 2 ;
        int count = 1 ;
        // Send data to processor 2:
        MPI_Send (&data, count, MPI_INT, recieving_Processor_rank, 0,                     MPI_COMM_WORLD) ;
        
        std::cout <<"Hello this is processor " <<rank <<std::endl ;
        std::cout <<data <<" is send to processor " <<recieving_Processor_rank <<std::endl ;
        
        // Again recieve modified data from processor 2:
        int sending_Processor_rank = 2 ;
        MPI_Status status ;
        
        // Get informations about the data recieved from processor 0:
        MPI_Probe (sending_Processor_rank, 0, MPI_COMM_WORLD, &status) ;
        MPI_Get_count (&status, MPI_INT, &count) ;
        
        MPI_Recv (&data, count, MPI_INT, sending_Processor_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        
        std::cout <<"Processor " <<rank <<" recieved " <<data <<" as modified data from processor " <<sending_Processor_rank <<std::endl ;
    }
    
    else if (rank == 1) // Processor 1
    {
        int data = 20 ;
        int recieving_Processor_rank = 2 ;
        int count = 1 ;
        // Send data to processor 2:
        MPI_Send (&data, count, MPI_INT, recieving_Processor_rank, 0,                     MPI_COMM_WORLD) ;
        
        std::cout <<"Hello this is processor " <<rank <<std::endl ;
        std::cout <<data <<" is send to processor " <<recieving_Processor_rank <<std::endl ;
        
        // Again recieve modified data from processor 2:
        int sending_Processor_rank = 2 ;
        MPI_Status status ;
        
        // Get informations about the data recieved from processor 0:
        MPI_Probe (sending_Processor_rank, 0, MPI_COMM_WORLD, &status) ;
        MPI_Get_count (&status, MPI_INT, &count) ;
        
        MPI_Recv (&data, count, MPI_INT, sending_Processor_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        
        std::cout <<"Processor " <<rank <<" recieved " <<data <<" as modified data from processor " <<sending_Processor_rank <<std::endl ;
    }
    
    else if (rank == 2) // Processor 2 modifies values recieved from 1 & 2
    {
        for (int r = 0; r < size-1; r++)
        {
            if (r == 0)
            {
                MPI_Status status ;
                int count ;
                // Get informations about the data recieved from processor 0:
                MPI_Probe (r, 0, MPI_COMM_WORLD, &status) ;
                MPI_Get_count (&status, MPI_INT, &count) ;
                
                int data ;
                // Recieve data from processor 0 and increment by 1:
                MPI_Recv (&data, count, MPI_INT, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
                
                data++ ;
                
                // Sends modified data back to processor 0:
                MPI_Send (&data, count, MPI_INT, r, 0, MPI_COMM_WORLD) ;
            }
            else
            {
                MPI_Status status ;
                int count ;
                // Get informations about the data recieved from processor 1:
                MPI_Probe (r, 0, MPI_COMM_WORLD, &status) ;
                MPI_Get_count (&status, MPI_INT, &count) ;
                
                int data ;
                // Recieve data from processor 1 and decrement by 1:
                MPI_Recv (&data, count, MPI_INT, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
                
                data-- ;
                
                // Sends modified data back to processor 1:
                MPI_Send (&data, count, MPI_INT, r, 0, MPI_COMM_WORLD) ;
            }
        }
    }
    
    MPI_Finalize () ;
}
