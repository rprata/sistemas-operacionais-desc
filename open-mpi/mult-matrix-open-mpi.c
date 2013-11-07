#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAG 7
    
int main (int argc, char ** argv) 
{
    int matrix_size; //Tamanho da matriz (N x N)
    int number_of_process; //Número de processos sendo utilizados
    int process_id; //Tag do processo
    int ** A, ** B, ** C; //Matrizes A, B e C. Novamente as matrizes tem seus elementos com valor 1 para simplificar a resposta.
    int * tmp; //Ponteiro que referencia posições das matrizes no auxilio do cálculo paralelo
 
    if (argc < 2) //caso não seja passado o argumento com a dimensão da matriz.
    {
		printf("Use: mpiexec -n <P> %s <N>,  onde 'N' é a dimensão da matriz unitária e 'P' é o número de processos\n", argv[0]);   
    	return 1;
    }
    
    matrix_size = atoi(argv[1]);

    //Para este código vamos considerar que o processo zero será o principal e todos estarão ligados a ele.  
    //Então teremos 1 máquina principal (id = 0) e outras que irão receber a fatia para o cálculo.
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    //Alocação de memória da matriz A
    if (process_id == 0) //No caso de ser o processo principal
    {
        tmp = (int *) malloc(sizeof(int) * matrix_size * matrix_size);
        A = (int **) malloc(sizeof(int *) * matrix_size);
        for (int i = 0; i < matrix_size; i++)
            A[i] = &tmp[i * matrix_size]; //alocação de memória para matriz A
    }
    else //No caso de ser os processos auxiliares
    {
        tmp = (int *) malloc(sizeof(int) * matrix_size * matrix_size / number_of_process);
        A = (int **) malloc(sizeof(int *) * matrix_size / number_of_process);
        for (int i = 0; i < matrix_size / number_of_process; i++)
            A[i] = &tmp[i * matrix_size]; //alocação de memória para matriz A
    }

    //Alocação de memória da matriz B
    tmp = (int *) malloc(sizeof(int) * matrix_size * matrix_size);
    B = (int **) malloc(sizeof(int *) * matrix_size);
    for (int i = 0; i < matrix_size; i++)
        B[i] = &tmp[i * matrix_size]; //alocação de memória para matriz B


    //Alocação de memória da matriz C - Resposta
    if (process_id == 0) //No caso de ser o processo principal
    {
        tmp = (int *) malloc(sizeof(int) * matrix_size * matrix_size);
        C = (int **) malloc(sizeof(int *) * matrix_size);
        for (int i = 0; i < matrix_size; i++)
            C[i] = &tmp[i * matrix_size]; //alocação de memória para matriz C
    }
    else //No caso de ser os processos auxiliares
    {
        tmp = (int *) malloc(sizeof(int) * matrix_size * matrix_size / number_of_process);
        C = (int **) malloc(sizeof(int *) * matrix_size / number_of_process);
        for (int i = 0; i < matrix_size / number_of_process; i++)
            C[i] = &tmp[i * matrix_size]; //alocação de memória para matriz C
    }

    //Inicialização das matrizes - No caso inicia-se no processo principal
    //Elementos de valor 1 para simplificar a resposta
    if (process_id == 0)
    {
        for (int i = 0; i < matrix_size; i++)
            for (int j = 0; j < matrix_size; j++)
            {
                A[i][j] = 1; 
                B[i][j] = 1;
            }
    }

    int offset, number_of_elements;

    //processo principal envia fatias para os demais processos
    if (process_id == 0)
    {
        offset = matrix_size / number_of_process;
        number_of_elements = (matrix_size / number_of_process) * matrix_size;
        for (int i = 1; i < number_of_process; i++) 
        {
            MPI_Send(A[offset], number_of_elements, MPI_INT, i, TAG, MPI_COMM_WORLD);
            offset += matrix_size / number_of_process;
        }
    }
    else //outros processos apenas recebem o valor de uma 'fatia' de A para calcular
    { 
        MPI_Recv(A[0], (matrix_size / number_of_process) * matrix_size, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Bcast(B[0], matrix_size * matrix_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Inicializando matriz C (resultado) com zero
    for (int i = 0; i < matrix_size / number_of_process; i++) 
    {
        for (int j = 0; j < matrix_size; j++)
        {
            C[i][j] = 0;
        }
    }

    //calculo de cada fatia
    for (int i = 0; i < matrix_size / number_of_process; i++) 
        for (int j = 0; j < matrix_size; j++)
            for (int k = 0; k < matrix_size; k++) 
                C[i][j] += A[i][k] * B[k][j];
        
    //Processo principal recebe o valor calculado de cada fatia produzida por um processo auxiliar
    if (process_id == 0)
    {
        offset = matrix_size / number_of_process;
        number_of_elements =  (matrix_size / number_of_process) * matrix_size;

        for (int i = 1; i < number_of_process; i++)
        {
            MPI_Recv(C[offset], number_of_elements, MPI_INT, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            offset += matrix_size / number_of_process;
        }
    }
    else
    {
        MPI_Send(C[0], (matrix_size / number_of_process) * matrix_size, MPI_INT, 0, TAG, MPI_COMM_WORLD);
    }

    //Impressão do resultado (no caso de uma matriz inferior a 20 x 20)
    if (process_id == 0 && matrix_size <= 20)
    {
        for (int i = 0; i < matrix_size; i++)
        {
            for (int j = 0; j < matrix_size; j++)
                printf("%d ", C[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}