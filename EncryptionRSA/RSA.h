#pragma once
#include <iostream>

struct Bigram
{
	long int first;
	long int second;
};

struct Trigram
{
	long int first;
	long int second;
	long int third;
};

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

	Trigram Encrypt(Bigram i);
	Bigram Decrypt(Trigram i);
	long int GreatestCommonDivisor(long int e, long int t);

	int GetNumberFromAlphabet(char c);
};