#include "RSA.h"

RSA::RSA()
{
	memset(encryptedText, 0, sizeof(encryptedText));
	memset(decryptedText, 0, sizeof(decryptedText));
}

void RSA::CalculateN()
{
	n = p * q;
}
void RSA::CalculateT()
{
	t = (p - 1) * (q - 1);
}
void RSA::CalculateE()
{
	for (long int i = 11; i < t; i++)
	{
		if (GreatestCommonDivisor(i, t) == 1)
		{
			e = i;
			break;
		}
	}
}
void RSA::CalculateD()
{
	long int k = 1;

	while (k % e != 0)
	{
		k = k + t;
	}

	d = (k / e);
}

long int RSA::Encrypt(long int i)
{
	long int current, result;

	current = i;
	result = 1;

	for (long int j = 0; j < e; j++)
	{
		result = result * current;
		result = result % n;
	}

	return result;
}

long int RSA::Decrypt(long int i)
{
	long int current, result;

	current = i;
	result = 1;

	for (long int j = 0; j < d; j++)
	{
		result = result * current;
		result = result % n;
	}

	return result;
}

long int RSA::GreatestCommonDivisor(long int e, long int t)
{
	while (e > 0)
	{
		long int myTemp;

		myTemp = e;
		e = t % e;
		t = myTemp;
	}

	return t;
}