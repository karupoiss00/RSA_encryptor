#include <iostream>
#include <string>
#include <math.h>
#include "RSA.h"

#define DIGITAL_SIGNATURE "ђЋ‘’€‘‹Ђ‚" //РОСТИСЛАВ (корявыми символами)

using namespace std;

void CryptStr(RSA* crypter, string str, bool isSignature = false);
void DecryptStr(RSA* crypter, size_t strLength);
void PrintCryptedStr(RSA* crypter, size_t strLength);
void PrintDecryptedStr(RSA* crypter, size_t strLength);

int main()
{
	setlocale(LC_ALL, "RU");
	RSA msgCrypter;
	RSA signatureCrypter;
	string msg;

	cout << "Enter p:" << endl;
	cin >> msgCrypter.p;
	cout << "Enter q:" << endl;
	cin >> msgCrypter.q;

	msgCrypter.CalculateN();
	msgCrypter.CalculateT();
	msgCrypter.CalculateE();
	msgCrypter.CalculateD();

	cout << "n = " << msgCrypter.n << endl;
	cout << "f(n) = " << msgCrypter.t << endl;
	cout << "K(e) = (" << msgCrypter.n << ", " << msgCrypter.e << ")" << endl;
	cout << "K(d) = (" << msgCrypter.n << ", " << msgCrypter.d << ")" << endl;

	signatureCrypter = msgCrypter;

	cout << "Message to encrypting:" << endl;
	cin.ignore();
	getline(cin, msg);

	CryptStr(&msgCrypter, msg);
	CryptStr(&signatureCrypter, string(DIGITAL_SIGNATURE), true);
	DecryptStr(&msgCrypter, msg.length());
	PrintCryptedStr(&msgCrypter, msg.length());
	PrintDecryptedStr(&msgCrypter, msg.length());
	cout << endl << "#####Signature#####";
	PrintCryptedStr(&signatureCrypter, string(DIGITAL_SIGNATURE).length());
	cout << endl;
	return 0;
}

void CryptStr(RSA* crypter, string str, bool isSignature)
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
		encrypted = crypter->Encrypt(decrypted, isSignature);
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