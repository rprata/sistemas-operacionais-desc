/*** 
 *** Trabalho de Sistemas Operacionais
 *** Aluno: Renan Prata
 *** Matricula: 2008.2.04357.11
 *** Professora: Cristiana Bentes
 *** 31/12/2013 - 12:13
 *** Obs1.: O software foi desenvolvido para rodar em ambiente unix/linux. Para compilar digite 'make' na linha de comando;
 *** Obs2.: Para executar o programa digite: mpiexec -n <P> sum-random-open-mpi, sendo que <P> é o numero de processos da aplicação;
 *** Obs3.: Para realizar um 'debug', descomente a linha 18 do código e recompile;
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h> 

#define TAG 7
// #define DEBUG

int main (int argc, char ** argv) 
{
    int number_of_process; //Número de processos sendo utilizados
    int process_id; //Id do processo
    int n; //Quantidade de termos da soma
    int sum = 0; //Resultado final da soma;
    int aux; 
    
    int * sequence; //Array que armazena a sequencia aleatoria
    
    double start_time, end_time;// Variaveis para calculo do tempo

    //Inicializa a sequencia sempre aleatória
    srand(time(NULL));

    //Para este código vamos considerar que o processo zero será o principal e todos estarão ligados a ele
    //Então teremos 1 máquina principal (id = 0) e outras que irão receber a fatia para o cálculo
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

   	//Recebe do usuario a quantidade de termos da sequencia
    if (process_id == 0)
    {
        printf("Digite a quantidade de termos da sequencia aleatoria que sera gerada: ");
        fflush(stdout);
        scanf("%d", &n);
    }	
	
    //Envia a todos os processos o valor de 'n'
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

   	//Inicializa e atribui valores aleatorios na sequencia
    if (process_id == 0) 
    {
    	int sum_par = 0;
    	sequence = (int *) malloc(sizeof(int) * n);
    	for (int i = 0; i < n; i++) 
    	{
    		sequence[i] = rand() % 100; //1;
    		
            #ifdef DEBUG 
            sum_par += sequence[i];
            printf("%d ", sequence[i]);
            #endif
        }
        
        #ifdef DEBUG
        printf("\n");
        printf("resultado = %d\n", sum_par);
        #endif
    }
    else
    {
    	if (process_id < number_of_process - 1)
    		sequence = (int *) malloc(sizeof(int) *  (n / number_of_process));
    	else
    		sequence = (int *) malloc(sizeof(int) *  (n / number_of_process + n % number_of_process));
    }

    //Calcula tempo inicial
    if (process_id == 0)
        start_time = MPI_Wtime();

    //Envia fatias da sequencia para todos os processos
    if (process_id == 0)
    {
        int offset = n / number_of_process;

        for (int i = 1; i < number_of_process; i++) 
        {
            if (i < number_of_process - 1)
                MPI_Send(&sequence[offset], n / number_of_process, MPI_INT, i, TAG, MPI_COMM_WORLD);
            else
                MPI_Send(&sequence[offset], n / number_of_process + n % number_of_process, MPI_INT, i, TAG, MPI_COMM_WORLD);

            offset += n / number_of_process;
        }
    }
    else //Outros processos apenas recebem o valor de uma 'fatia' de sequence para calcular
    {
        if (process_id < number_of_process - 1) 
        	MPI_Recv(&sequence[0], n / number_of_process, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        else
        	MPI_Recv(&sequence[0], n / number_of_process + n % number_of_process, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    //Soma cada fatia individualmente
    for (int i = 0; i < ((process_id < number_of_process - 1) ? (n / number_of_process) 
        :  (n / number_of_process + n % number_of_process)); i++)
    {
        sum += sequence[i];
    }
    
    //Barreira pra controle
    MPI_Barrier(MPI_COMM_WORLD); 

    //Processo principal recebe o valor calculado de cada fatia produzida por um processo auxiliar
    if (process_id == 0)
    {
        for (int i = 1; i < number_of_process; i++)
        {
            MPI_Recv(&aux, 1, MPI_INT, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += aux;
        }
    }
    else
    {
        MPI_Send(&sum, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
    }

    //Barreira pra controle	
    MPI_Barrier(MPI_COMM_WORLD);
	
	//Calculo do tempo de execução	
    if (process_id == 0)
    {
        end_time = MPI_Wtime();
        printf("O resultado final foi %d e o tempo de execução foi de %.6f\n", sum, end_time - start_time);
    }

    //Finaliza o MPI
    MPI_Finalize();

    return 0;
}