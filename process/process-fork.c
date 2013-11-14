#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	int pid;

	/* fork a child process */
	fork();
	/* fork another child process */
	fork();

	/* and fork another */
	fork();

	pid = fork();	
	if (pid == -1)
		printf("problemas ao criar o filho!\n");
	else if (pid == 0)
		printf("Eu sou o filho: %d\n", getpid());
	else
		printf("Eu sou o pai e criei: %d\n", pid);
	
	return 0;
}
