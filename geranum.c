#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DECRYPTION_AND_ENCRYPTION_COUNTER 1

void createPrivateAndPublicKeys(int firstPrime, int secondPrime);
int getEncryptionNumber(int baseNumber, int coprimesOfBaseNumber);
int getDecryptionNumber(int baseNumber, int coprimesOfBaseNumber);
int isPrime(int number);
void help();

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		help();
		return -1;
	}
	int firstPrime = atoi(argv[1]);
	int secondPrime = atoi(argv[2]);
	if (!isPrime(firstPrime) || !isPrime(secondPrime))
	{
		printf("Argumentos invalidos. Os numeros fornecidos devem ser primos.\n");
		return -1;
	}
	printf("Criando chaves de criptografia...\n");
	createPrivateAndPublicKeys(firstPrime, secondPrime);
	printf("Geradas chaves publica <numcripto.txt> e privada <numdescripto.txt.>\n");
	return 0;
}

void createPrivateAndPublicKeys(int firstPrime, int secondPrime)
{
	int baseNumber = firstPrime * secondPrime;
	int coprimesOfBaseNumber = (firstPrime - 1) * (secondPrime - 1);
	int encryptionNumber = getEncryptionNumber(baseNumber, coprimesOfBaseNumber);
	int decryptionNumber = getDecryptionNumber(encryptionNumber, coprimesOfBaseNumber);
	FILE *fp;
	fp = fopen("./numcripto.txt", "w");
	fprintf(fp, "RSA %d %d", encryptionNumber, baseNumber);
	fclose(fp);
	fp = fopen("./numdescripto.txt", "w");
	fprintf(fp, "RSA %d %d", decryptionNumber, baseNumber);
	fclose(fp);
}

int getEncryptionNumber(int baseNumber, int coprimesOfBaseNumber)
{
	int counter = 0;
	for (int i = 2; i < baseNumber; i++)
	{
		if (baseNumber % i == 0 || coprimesOfBaseNumber % i == 0)
		{
			continue;
		}
		if (i > 1 && i < coprimesOfBaseNumber)
		{
			counter++;
			if (counter == DECRYPTION_AND_ENCRYPTION_COUNTER)
			{
				return i;
			}
		}
	}
	return 0;
}

int getDecryptionNumber(int encryptionNumber, int coprimesOfBaseNumber)
{
	int counter = 0;
	for (int i = 1; 1; i++)
	{
		if ((i * encryptionNumber) % coprimesOfBaseNumber == 1)
		{
			counter++;
			if (counter == DECRYPTION_AND_ENCRYPTION_COUNTER)
			{
				return i;
			}
		}
	}
}

int isPrime(int number)
{
	if (number <= 1)
		return 0;
	if (number == 2)
		return 1;
	for (int i = 2; i <= sqrt(number); i++)
	{
		if (number % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

void help()
{
	printf("Uso: geranum <num1> <num2>\n  <num1> - Um numero PRIMO qualquer\n  <num2> - Um numero PRIMO qualquer\n");
}