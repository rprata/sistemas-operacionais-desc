#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100

int soma = 0;
pthread_mutex_t mut;

void * funcao_do_emanuel(void * arg)
{
	pthread_mutex_lock(&mut);
	soma += *((int *) arg);
	pthread_mutex_unlock(&mut);
}

int main (int argc, char ** argv)
{
	pthread_t * p = (pthread_t *) malloc(N*sizeof(pthread_t));

	int valor = 1;
	
	pthread_mutex_init(&mut, NULL);

	for (int i = 0; i < N; i++)
		pthread_create(&p[i], NULL, funcao_do_emanuel, &valor);

	for (int j = 0; j < N; j++)
		pthread_join(p[j], NULL);

	printf("%d\n", soma);

	free(p);
	pthread_mutex_destroy(&mut);

	return 0;
}

