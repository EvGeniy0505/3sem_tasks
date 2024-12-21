#include <stdio.h>

int main (const int argc, const char* argv[], const char* envp[]) {

	printf("Cmd options:\n");

	for (int i = 0; i < argc; i++)
    {
		printf("%s\n", argv[i]);
    }

	printf("Env:\n");

	int i = 0;


	while (envp[i] != NULL)
    {
		printf("%s\n", envp[i++]);
    }

	return 0;
}
