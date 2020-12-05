#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void help();
int isPrime(int number);

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
	return 0;
}

void help()
{
	printf("Uso: geranum <num1> <num2>\n  <num1> - Um numero PRIMO qualquer\n  <num2> - Um numero PRIMO qualquer\n");
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