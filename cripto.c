#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help();
void decryptMessage(char *message);
void encryptMessage(char *message);
int getEncryptedChar(int key, int base, int c);
int modFactor(int base, int exp, int mod);

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
void decryptMessage(char *message)
{
	char decryptionFile[1000];
	FILE *fptr;
	if ((fptr = fopen("numdescripto.txt", "r")) == NULL)
	{
		printf("Erro! Não foram geradas as chaves de encriptacao\n");
		return;
	}
	fscanf(fptr, "%[^EOF]", decryptionFile);
	printf("DecriptionFile:%s\n", decryptionFile);
	char *delimitedFile = strtok(decryptionFile, " ");
	delimitedFile = strtok(NULL, " ");
	int decryptionNumber = atoi(delimitedFile);
	delimitedFile = strtok(NULL, " ");
	int baseNumber = atoi(delimitedFile);
	printf("Decryption: %d, Base: %d, Message: %s\n", decryptionNumber, baseNumber, message);
	for (int i = 0; i < (strlen(message)); i++)
	{
		printf("%d -> %c\n", message[i], message[i]);
	}

	fclose(fptr);
}
void encryptMessage(char *message)
{

	char encryptionFile[1000];
	FILE *fptr;
	if ((fptr = fopen("numcripto.txt", "r")) == NULL)
	{
		printf("Erro! Não foram geradas as chaves de encriptacao\n");
		return;
	}
	fscanf(fptr, "%[^EOF]", encryptionFile);
	char *delimitedFile = strtok(encryptionFile, " ");
	delimitedFile = strtok(NULL, " ");
	int encryptionNumber = atoi(delimitedFile);
	delimitedFile = strtok(NULL, " ");
	int baseNumber = atoi(delimitedFile);
	printf("Key: %d, Base: %d, Message: %s\n", encryptionNumber, baseNumber, message);
	fclose(fptr);
	fptr = fopen("saida.txt", "w+");
	for (int i = 0; i < (strlen(message)); i++)
	{
		fprintf(fptr, "%d ", getEncryptedChar(encryptionNumber, baseNumber, message[i]));
	}
	fclose(fptr);
}

int getEncryptedChar(int key, int baseNumber, int character)
{
	int result = 1;
	for (int i = 1; i <= 32; i++)
	{
		int value = (int)pow(2, i);
		if ((key & value) == value)
		{
			result *= modFactor(character, value, baseNumber);
			printf("Resultado: %d\n", result);
			continue;
		}
	}
	return result % baseNumber;
}
int modFactor(int base, int exp, int mod)
{
	if (exp == 0)
		return 1;
	if (exp == 1)
		return base % mod;
	return ((modFactor(base, exp / 2, mod) % mod) * (modFactor(base, exp / 2, mod) % mod)) % mod;
}

void help()
{
	printf("Uso: cripto [opcoes] <mensagem>\nOpcoes:\n  -d\tDesencriptar a mensagem\n  -c\tEncriptar a mensagem\n");
}