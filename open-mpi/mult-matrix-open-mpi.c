#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char ** argv) 
{
    int matrix_size, number_of_process, process_id;
    if (argc < 2)
    {
		printf("Use: mpiexec -n <P> %s <N>,  onde 'N' é a dimensão da matriz unitária e 'P' é o número de processos\n", argv[0]);   
    	return 1;
    }
    
    matrix_size = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    printf("Hello from processor %d of %d\n", process_id, number_of_process);
    
    MPI_Finalize();

    return 0;
}