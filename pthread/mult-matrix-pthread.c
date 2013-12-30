#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


int ** A, ** B, ** C; //Matriz A, B e C. No caso unitarias para facilitar a resposta
int number_of_threads; //Numero de threads
int matrix_size; //Tamanho da matriz (N x N)

typedef struct matrix_data_struct {
    int id;
    int number_of_threads;
    int matrix_size;
    int ** A;
    int ** B;
    int ** C;
} Matrix_Data;

struct timespec initial_time, end_time;

void multiplyMatrices (int matrix_id, int matrix_size, int number_of_threads, int ** mat_A, int ** mat_B, int ** mat_C);

void * function_pthread (void * arg);
void createThreads (pthread_t * threads, int number_of_threads, int matrix_size, int ** mat_A, int ** mat_B, int ** mat_C);
void joinThreads (pthread_t * p_threads, int number_of_threads);

int ** allocateMatrix (int matrix_size);
void generateMatrix(int ** mat, int matrix_size);
void printMatrix (int ** mat, int matrix_size, char * matrix_name);


int main (int argc, char ** argv)
{
	if (argc != 3) 
	{
		printf("Use: %s <N> <T>,  onde 'N' é a dimensão da matriz unitária e 'T' é o número de threads.\n", argv[0]);
		return 1;
	}

	//Retira valores dos argumentos passados pela linha de comando
	matrix_size = atoi(argv[1]);
	number_of_threads = atoi(argv[2]);

	//Aloca espaço para variáveis e ponteiros para colunas
	A = allocateMatrix(matrix_size);
	B = allocateMatrix(matrix_size);
	C = allocateMatrix(matrix_size);

	//Gera matrizes A e B
	generateMatrix(A, matrix_size);
	generateMatrix(B, matrix_size);
	generateMatrix(C, matrix_size);

	//Imprime A e B (teste)
	if (matrix_size < 20)
	{
		printMatrix(A, matrix_size, "A");
		printMatrix(B, matrix_size, "B");	
	}

	//Ponteiro com threads
	pthread_t * p_threads;
	//Alocação de espaço para threads de acordo com o número de threads
	p_threads = (pthread_t *) malloc(number_of_threads * sizeof(pthread_t));

	//Captura tempo inicial
	clock_gettime(CLOCK_MONOTONIC, &initial_time);

	//Criação de threads
	createThreads(p_threads, number_of_threads, matrix_size, A, B, C);

	//Join das threads
	joinThreads(p_threads, number_of_threads);

	//Captura tempo final
	clock_gettime(CLOCK_MONOTONIC, &end_time);
  	
  	//imprime respostas
	if (matrix_size < 20)
		printMatrix(C, matrix_size, "C");

	//Calcula tempo final
	double elapsed = end_time.tv_sec - initial_time.tv_sec;
	elapsed += (end_time.tv_nsec - initial_time.tv_nsec) / 1000000000.0;
 	printf ("O tempo de processamento foi de: %f segundos\n", elapsed);   
  
	return 0;
}

//Algoritmo de produto de matrizes
void multiplyMatrices (int matrix_id, int matrix_size, int number_of_threads, int ** mat_A, int ** mat_B, int ** mat_C)
{
	int i, j, k;
	int start_row, end_row;

	//calculo para as bordas (alcance) destas threads.
	start_row = matrix_id * (matrix_size / number_of_threads);

	if (matrix_id == number_of_threads - 1)
	{
		end_row = (matrix_id + 1) * (matrix_size/number_of_threads) + matrix_size % number_of_threads;
	}
	else
	{
		end_row = (matrix_id + 1) * (matrix_size/number_of_threads);
	}

	for (i = start_row; i < end_row; i++)
	{
		for (j = 0; j < matrix_size; j++) 
		{
			for (k = 0; k < matrix_size; k++)
			{
				mat_C[i][j] += mat_A[i][k] * mat_B[k][j];
			}
		}
	}

}

//Função template para pthread_create
void * function_pthread (void * arg)
{
	Matrix_Data * m_data = (Matrix_Data *) arg;
	multiplyMatrices(m_data->id, m_data->matrix_size, m_data->number_of_threads, m_data->A, m_data->B, m_data->C);
	return (void *) NULL;
}

//Aguarda até o término da execução das threads
void joinThreads (pthread_t * p_threads, int number_of_threads)
{
	int i;
	for (i = 0; i < number_of_threads; i++)
		pthread_join(p_threads[i], NULL);
}

//Cria threads
void createThreads (pthread_t * threads, int number_of_threads, int matrix_size, int ** mat_A, int ** mat_B, int ** mat_C) 
{
	int i;
	Matrix_Data * m_data;
	for (i = 0; i < number_of_threads; i++) 
	{
		m_data = (Matrix_Data *) malloc(sizeof(Matrix_Data));
		m_data->id = i;
		m_data->number_of_threads = number_of_threads;
		m_data->matrix_size = matrix_size;
		m_data->A = mat_A;
		m_data->B = mat_B;
		m_data->C = mat_C;

    	pthread_create(&threads[i], NULL, function_pthread, (void *)(m_data));
  	}
}

//Aloca memória para matriz
int ** allocateMatrix (int matrix_size) 
{
	int i;
	int * values, ** temp;

  	// alocação de espaço para valores
  	values = malloc (matrix_size * matrix_size * sizeof(int));

  	// alocação de ponteiros para vetores
 	temp = malloc (matrix_size * sizeof(int *));

	for (i = 0; i < matrix_size; i++)
  		temp[i] = &(values[i * matrix_size]);

 	return temp;
}

// Gera matriz N X N com todos os elementos 1
void generateMatrix(int ** mat, int matrix_size) 
{
	int i, j;
	for (i = 0; i < matrix_size; i++)
    	for (j = 0; j < matrix_size; j++) 
      		mat[i][j] = 1;

}

//Imprime matriz NxN no console
void printMatrix (int ** mat, int matrix_size, char * matrix_name)
{
	int i,j;
	
	printf ("A matriz %s %d X %d é:\n", matrix_name, matrix_size, matrix_size);
	for (i = 0; i < matrix_size; i++)
	{
		for (j = 0; j < matrix_size; j++)
	  		printf ("%d ", mat[i][j]);
		printf ("\n");
	}
	printf("\n");
}