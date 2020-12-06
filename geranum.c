#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DECRYPTION_NUMBERT_COUNTER 2

void help();
int isPrime(int number);
void createPrivateAndPublicKeys(int firstPrime, int secondPrime);
int getEncryptionNumber(int baseNumber, int coprimesOfBaseNumber);
int getDecryptionNumber(int baseNumber, int coprimesOfBaseNumber);

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
		printf("Argumentos invalidos. Os numeros devem ser primos");
		return -1;
	}
	createPrivateAndPublicKeys(firstPrime, secondPrime);
	return 0;
}

void help()
{
	printf("Uso: geranum <num1> <num2>\n  <num1> - Um numero PRIMO qualquer\n  <num2> - Um numero PRIMO qualquer\n");
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
	printf("base: %d , encryption: %d, decryption: %d", baseNumber, encryptionNumber, decryptionNumber);
}

int getEncryptionNumber(int baseNumber, int coprimesOfBaseNumber)
{
	int encryptionNumber = 0;
	for (int i = 2; i < baseNumber; i++)
	{
		if (baseNumber % i == 0 || coprimesOfBaseNumber % i == 0)
		{
			continue;
		}
		if (i > 1 && i < coprimesOfBaseNumber)
		{
			encryptionNumber = i;
		}
	}
	return encryptionNumber;
}
int getDecryptionNumber(int encryptionNumber, int coprimesOfBaseNumber)
{
	int counter = 0;
	for (int i = 1; 1; i++)
	{
		if ((i * encryptionNumber) % coprimesOfBaseNumber == 1)
		{
			counter++;
			if (counter == DECRYPTION_NUMBERT_COUNTER)
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