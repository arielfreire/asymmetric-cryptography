#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help();

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		help();
		return -1;
	}
	if (!strcmp(argv[1], "-c"))
	{
		printf("Encriptando arquivo.\n");
	}
	else if (!strcmp(argv[1], "-d"))
	{
		printf("Desincriptando arquivo.\n");
	}
	else
	{
		help();
		return -1;
	}

	return 0;
}

void help()
{
	printf("Uso: cripto [opcoes] <mensagem>\nOpcoes:\n  -d\tDesencriptar a mensagem\n  -c\tEncriptar a mensagem\n");
}