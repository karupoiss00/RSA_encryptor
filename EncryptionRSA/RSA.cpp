#include "RSA.h"

RSA::RSA()
{
	memset(encryptedText, 0, sizeof(encryptedText));
	memset(decryptedText, 0, sizeof(decryptedText));
	alphabet = "€‚ƒ„…ğ†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ .,!";
	alphabetRU = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß .,!";
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

Trigram RSA::Encrypt(Bigram i, bool isSignature)
{
	long int firstSymbol = GetNumberFromAlphabet((char)i.first);
	long int secondSymbol = GetNumberFromAlphabet((char)i.second);
	long int current = firstSymbol * alphabet.length() + secondSymbol;
	long int result = 1;

	Trigram encrypted;
	if (isSignature)
	{
		for (long int j = 0; j < d; j++)
		{
			result = result * current;
			result = result % n;
		}
	}
	else
	{
		for (long int j = 0; j < e; j++)
		{
			result = result * current;
			result = result % n;
		}
	}

	encrypted.first = (result / (alphabet.length() * alphabet.length())) % alphabet.length();
	encrypted.second = (result / alphabet.length()) % alphabet.length();
	encrypted.third = result % alphabet.length();

	return encrypted;
}

Bigram RSA::Decrypt(Trigram i)
{
	long int current = i.first * alphabet.length() * alphabet.length() 
						+ i.second * alphabet.length() 
						+ i.third;
	long int result = 1;

	Bigram decrypted;

	for (long int j = 0; j < d; j++)
	{
		result = result * current;
		result = result % n;
	}

	decrypted.first = result / alphabet.length();
	decrypted.second = result % alphabet.length();

	return decrypted;
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

int RSA::GetNumberFromAlphabet(char c)
{
	for (size_t i = 0; i < alphabet.length(); i++)
	{
		if (c == alphabet[i])
		{
			return i;
		}
	}
	return -1;
}

RSA RSA::operator=(RSA right)
{
	if (this == &right)
	{
		return *this;
	}
	p = right.p;
	q = right.q;
	n = right.n;
	t = right.t;
	e = right.e;
	d = right.d;

	return *this;
}