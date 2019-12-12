#pragma once
#include <iostream>

struct RSA
{
	long int p, q, n, t, e, d;
	long int encryptedText[100];
	long int decryptedText[100];
	std::string alphabet;
	std::string alphabetRU;

	RSA();

	void CalculateN();
	void CalculateT();
	void CalculateE();
	void CalculateD();

	long int Encrypt(long int i);
	long int Decrypt(long int i);
	long int GreatestCommonDivisor(long int e, long int t);

	int GetNumberFromAlphabet(char c);
};