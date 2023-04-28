#include <mpi.h>
#include <iostream>

int main(int argc, char** argv)
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int np;
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    // Get the rank of the process
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, pid, np);

    // Finalize the MPI environment.
    MPI_Finalize();
}
