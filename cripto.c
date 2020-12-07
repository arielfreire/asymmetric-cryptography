#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encryptMessage(char *message);
void decryptMessage(char *message);
void getSpaceDelimitedArray(char string[], int *array);
int getEncryptedCharacter(int key, int base, int c);
int modularFactoring(int base, int exp, int mod);
void help();

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		help();
		return -1;
	}
	if (!strcmp(argv[1], "-c"))
	{
		encryptMessage(argv[2]);
	}
	else if (!strcmp(argv[1], "-d"))
	{
		decryptMessage(argv[2]);
	}
	else
	{
		help();
		return -1;
	}

	return 0;
}

void encryptMessage(char *message)
{
	int array[1000] = {0};
	getSpaceDelimitedArray(message, array);
	char encryptionFile[1000];
	FILE *fptr;
	if ((fptr = fopen("numcripto.txt", "r")) == NULL)
	{
		printf("Erro! Não foram geradas as chaves de criptografia\n");
		return;
	}
	printf("Criptografando mensagem...\n");
	fscanf(fptr, "%[^EOF]", encryptionFile);
	char *delimitedFile = strtok(encryptionFile, " ");
	delimitedFile = strtok(NULL, " ");
	int encryptionNumber = atoi(delimitedFile);
	delimitedFile = strtok(NULL, " ");
	int baseNumber = atoi(delimitedFile);
	fclose(fptr);
	fptr = fopen("saida.txt", "w+");

	for (int i = 0; i < (sizeof(array)); i++)
	{
		if (array[i] == 0)
			break;
		fprintf(fptr, "%d ", getEncryptedCharacter(encryptionNumber, baseNumber, array[i]));
	}
	fclose(fptr);
	printf("Mensagem criptografada.\n");
}

void decryptMessage(char *message)
{
	int array[1000] = {0};
	getSpaceDelimitedArray(message, array);
	char decryptionFile[1000];
	FILE *fptr;
	if ((fptr = fopen("numdescripto.txt", "r")) == NULL)
	{
		printf("Erro! Não foram geradas as chaves de criptografia.\n");
		return;
	}
	printf("Descriptografando mensagem...\n");
	fscanf(fptr, "%[^EOF]", decryptionFile);
	fclose(fptr);
	fptr = fopen("saida.txt", "w+");
	char *delimitedFile = strtok(decryptionFile, " ");
	delimitedFile = strtok(NULL, " ");
	int decryptionNumber = atoi(delimitedFile);
	delimitedFile = strtok(NULL, " ");
	int baseNumber = atoi(delimitedFile);
	for (int i = 0; i < (sizeof(array)); i++)
	{
		if (array[i] == 0)
			break;
		fprintf(fptr, "%d ", getEncryptedCharacter(decryptionNumber, baseNumber, array[i]));
	}
	fclose(fptr);
	printf("Mensagem descriptografada.\n");
}

int getEncryptedCharacter(int key, int baseNumber, int character)
{
	int result = 1;
	for (int i = 32; i >= 0; i--)
	{
		int value = (int)pow(2, i);
		if ((key & value) == value)
		{
			result *= modularFactoring(character, value, baseNumber);
			continue;
		}
	}
	return result % baseNumber;
}

int modularFactoring(int base, int exp, int mod)
{
	if (exp == 0)
		return 1;
	if (exp == 1)
		return base % mod;
	return ((modularFactoring(base, exp / 2, mod) % mod) * (modularFactoring(base, exp / 2, mod) % mod)) % mod;
}

void getSpaceDelimitedArray(char string[], int *array)
{
	int i = 0;
	char *delimitedFile = strtok(string, " ");
	while (delimitedFile != NULL)
	{
		array[i] = atoi(delimitedFile);
		i++;
		delimitedFile = strtok(NULL, " ");
	}
}

void help()
{
	printf("Uso: cripto [opcoes] <mensagem>\nOpcoes:\n  -d\tDesencriptar a mensagem\n  -c\tEncriptar a mensagem\n");
}