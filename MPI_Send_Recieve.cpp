//
//  MPI_Send_Recieve.cpp
//  
//
//  Created by Shambhavi Nandan on 3/17/20.
//

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
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
    if (size < 3)
    {
        printf("Currently there are %d processors \n", size) ;
        printf("The current program requires exactly 3 processors\n") ;
        MPI_Abort (MPI_COMM_WORLD, 1) ;
    }
    
    // Send and Recieve functionality :
    
    if (rank == 0) // Processor 0
    {
        int send_data = 10 ;
        int recieving_Processor_rank = 2 ;
        int count = 1 ;
        // Send data to processor 2:
        MPI_Send (&send_data, count, MPI_INT, recieving_Processor_rank, 0,                     MPI_COMM_WORLD) ;
        
        printf("Hello this is processor %d:\n", rank) ;
        printf("........%d is send to processor %d\n", send_data, recieving_Processor_rank) ;
    }
    
    else if (rank == 1) // Processor 1
    {
        int send_data = 20 ;
        int recieving_Processor_rank = 2 ;
        int count = 1 ;
        // Sending data to processor 2:
        MPI_Send (&send_data, count, MPI_INT, recieving_Processor_rank, 0, MPI_COMM_WORLD) ;
        
        printf("Hello this is processor %d:\n", rank) ;
        printf("........%d is send to processor %d\n", send_data, recieving_Processor_rank) ;
    }
    
    else if (rank == 2) // Processor 2 add values recieved from 1 & 2
    {
        int data_1 ;
        int data_2 ;
        int rank_1 = 0 ;
        int rank_2 = 1 ;
        int count = 1 ;
        // Recieve data from processor 0:
        MPI_Recv (&data_1, count, MPI_INT, rank_1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        // Recieve data from processor 1:
        MPI_Recv (&data_2, count, MPI_INT, rank_2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        // Add the data recieved from processor 0 and 1:
        int add = data_1 + data_2 ;
        
        printf("Hello this is processor %d:\n", rank) ;
        printf("........ I recieved %d from processor %d and \n", data_1, rank_1) ;
        printf("........ I recieved %d from processor %d and \n", data_2, rank_2) ;
        printf("........ The sum of two data are: %d\n", add) ;

    }
    
    MPI_Finalize () ;
}
