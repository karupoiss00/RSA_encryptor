#include <iostream>
#include <string>
#include <math.h>
#include "RSA.h"

using namespace std;

void CryptStr(RSA* crypter, string str);
void DecryptStr(RSA* crypter, size_t strLength);
void PrintCryptedStr(RSA* crypter, size_t strLength);
void PrintDecryptedStr(RSA* crypter, size_t strLength);

int main()
{
	setlocale(LC_ALL, "RU");
	RSA crypter;
	string msg;

	cout << "Enter p:" << endl;
	cin >> crypter.p;
	cout << "Enter q:" << endl;
	cin >> crypter.q;

	crypter.CalculateN();
	crypter.CalculateT();
	crypter.CalculateE();
	crypter.CalculateD();

	cout << "n = " << crypter.n << endl;
	cout << "f(n) = " << crypter.t << endl;
	cout << "K(e) = (" << crypter.n << ", " << crypter.e << ")" << endl;
	cout << "K(d) = (" << crypter.n << ", " << crypter.d << ")" << endl;

	cout << "Message to encrypting:" << endl;
	cin.ignore();
	getline(cin, msg);

	CryptStr(&crypter, msg);
	DecryptStr(&crypter, msg.length());
	PrintCryptedStr(&crypter, msg.length());
	PrintDecryptedStr(&crypter, msg.length());

	cout << endl;
	return 0;
}

void CryptStr(RSA* crypter, string str)
{
	size_t j = 0;
	Bigram decrypted;
	Trigram encrypted;

	if (str.length() % 2 != 0)
	{
		str += ' ';
	}

	for (size_t i = 0; i < str.length(); i += 2)
	{
		decrypted.first = str[i]; 
		decrypted.second = str[i + 1];
		encrypted = crypter->Encrypt(decrypted);
		crypter->encryptedText[j] = encrypted.first;
		crypter->encryptedText[j + 1] = encrypted.second;
		crypter->encryptedText[j + 2] = encrypted.third;
		j += 3;
	}
	crypter->encryptedText[j + 1] = -1;
}

void DecryptStr(RSA* crypter, size_t strLength)
{
	size_t j = 0;
	Trigram encrypted;
	Bigram decrypted;
	
	for (size_t i = 0; j < strLength; j += 2)
	{
		encrypted.first = crypter->encryptedText[i];
		encrypted.second = crypter->encryptedText[i + 1];
		encrypted.third = crypter->encryptedText[i + 2];

		decrypted = crypter->Decrypt(encrypted);
		crypter->decryptedText[j] = decrypted.first;
		crypter->decryptedText[j + 1] = decrypted.second;
		i += 3;
	}
}
void PrintCryptedStr(RSA* crypter, size_t strLength)
{
	size_t i = 0;
	cout << endl << "Encrypted:" << endl;
	
	while (crypter->encryptedText[i] != -1)
	{
		cout << static_cast<char>(crypter->alphabetRU[crypter->encryptedText[i]]);
		i++;
	}
}
void PrintDecryptedStr(RSA* crypter, size_t strLength)
{
	cout << endl << "Decrypted:" << endl;
	for (size_t i = 0; i < strLength; i++)
	{
		cout << static_cast<char>(crypter->alphabetRU[crypter->decryptedText[i]]);
	}
}